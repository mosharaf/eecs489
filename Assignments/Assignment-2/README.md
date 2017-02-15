# Assignment 2: Video Streaming via CDN

### Due: February 24th, 2017 at 11:59 PM

## Overview

Video traffic dominates the Internet. In this project, you will explore how video content distribution networks (CDNs) work. In particular, you will implement adaptive bitrate selection, DNS load balancing, and an HTTP proxy server to stream video at high bit rates from the closest server to a given client.

<img src="real-CDN.png" title="Video CDN in the wild" alt="" width="350" height="256"/>

### Video CDNs in the Real World
The figure above depicts a high level view of what this system looks like in the real world. Clients trying to stream a video first issue a DNS query to resolve the service's domain name to an IP address for one of the CDN's content servers. The CDN's authoritative DNS server selects the “best” content server for each particular client based on
(1) the client's IP address (from which it learns the client's geographic location) and
(2) current load on the content servers (which the servers periodically report to the DNS server).

Once the client has the IP address for one of the content servers, it begins requesting chunks of the video the user requested. The video is encoded at multiple bitrates; as the client player receives video data, it calculates the throughput of the transfer and requests the highest bitrate the connection can support.

### Video CDN in this Assignment
Implementing an entire CDN is difficult; instead, you'll focus on a simplified version. First, your entire system will run on one host and rely on mininet to run several processes with arbitrary IP addresses on one machine. Mininet will also allow you to assign arbitrary link characteristics (bandwidth and latency) to each pair of “end hosts” (processes).

<img src="our-CDN.png" title="Video CDN in assignment 2" alt="" width="330" height="111"/>

You'll write the gray-shaded components in the figure above.

**Browser.** You'll use an off-the-shelf web browser (Firefox) to play videos served by your CDN (via your proxy).

**Proxy.** Rather than modify the video player itself, you will implement adaptive bitrate selection in an HTTP proxy. The player requests chunks with standard HTTP GET requests; your proxy will intercept these and modify them to retrieve whichever bitrate your algorithm deems appropriate. To simulate multiple clients, you will launch multiple instances of your proxy.

**Web Server.** Video content will be served from an off-the-shelf web server (Apache). As with the proxy, you will run multiple instances of Apache on different IP addresses to simulate a CDN with several content servers.

**DNS Server.** You will implement a simple DNS that supports only a small portion of actual DNS's functionality. Your server will respond to each request with the “best” server for that particular client.

To summarize, this assignment has the following components:

* [Part 1](#part1): Bitrate Adaptation in HTTP Proxy
* [Part 2](#part2): DNS Load Balancing
* [Submission Instructions](#submission-instr)

## Learning Outcomes

After completing this programming assignment, students should be able to:

* Explain how HTTP proxies, DNS servers, and video CDNs work
* Create topologies and change network characteristics in Mininet to test networked systems

## Clarifications

* For the proxy you implement in part 1, you will need to parse some HTTP traffic. To make your life easier for this project, you don't need to be concerned about parsing all the information in these HTTP messages. There are only two things that you need to care about searching for: "\r\n\r\n" and "Content-Length:". The former is used to denote the end of an HTTP header, and the latter is used to signify the size of the HTTP body in bytes.

* While testing the proxy you implement in part 1, you may notice that one browser may sometimes open multiple connections to your proxy server. Your proxy should still continue to function as expected in this case. In order to account for these multiple connections, you may use the browser IP address to uniquely identify each connection (this implies that while testing your proxy server, each browser will have a unique IP address. For example, only one browser will have an IP address of 10.0.0.2).

<a name="part1"></a>

## Environment setup

[We are providing a VM](http://web.eecs.umich.edu/~mosharaf/EECS489/W17/eecs489p2.ova) that has all the components you need to get started on the assignment. This VM includes mininet, Apache, and all the files we will be streaming in this project. Both the username and password for this VM are `proj2`. To start the Apache server, simply run the python script we provide by doing the following:

`python start_server.py <host_number>`

Here `<host_number>` is a required command line argument that specifies what host you are running on Mininet. This is important as if you're running on h1 in Mininet (which is given the IP address 10.0.0.1), passing in `1` into the `<host_number>` argument will help ensure that the Apache server instance will be bound to the 10.0.0.1 IP address. The `<host_number>` argument must be between 1 and 8.

If you are testing locally, and simply wish to launch the server locally, you can run the following command:

`/usr/local/apache2/bin/apachectl start`

For this project, we will be using an off the shelf browser (in this case, it is Firefox). To launch Firefox for this project, run the following command:

`python launch_firefox.py <profile_num>`

Here `<profile_num>` is a required command line argument that specifies the instance of Firefox you are launching. We support launching profiles 1-8, however, should you feel the need to test more thoroughly, you can launch it with a different number and simply create a new profile as needed. To ensure a separate connection for each instance of Firefox, we recommend that you launch Firefox with a different profile number (otherwise you might notice that different Firefox instances will sometimes share a connection with your proxy browser).

**NOTE:** For this project, we are disabling caching in the browser. If you do choose to create a new profile, please be sure to go to the `about:config` page and set both `browser.cache.disk.enable` and `browser.cache.memory.enable` to `false`.

## Part 1: Bitrate Adaptation in HTTP Proxy

Many video players monitor how quickly they receive data from the server and use this throughput value to request better or lower quality encodings of the video, aiming to stream the highest quality encoding that the connection can handle. Instead of modifying an existing video client to perform bitrate adaptation, you will implement this functionality in an HTTP proxy through which your browser will direct requests.

You are to implement a simple HTTP proxy, `miProxy`. It accepts connections from web browsers, modifies video chunk requests as described below, resolves the web server's DNS name, opens a connection with the resulting IP address, and forwards the modified request to the server. Any data (the video chunks) returned by the server should be forwarded, *unmodified*, to the browser.

`miProxy` should listen for browser connections on `INADDR_ANY` on the port specified on the command line. It should then connect to web servers either specified on the command line (see below) or issue a DNS query to find out the IP address of the server to contact (this is covered in part 2).

<img src="proxy-overview.png" title="Video CDN in the wild" alt="" width="534" height="171"/>

It should accept multiple concurrent connections using `select()` and be able to handle the required HTTP 1.1 requests for this assignment (e.g., HTTP `GET`). You might find the `select()` [demo covered in discussion](https://github.com/mosharaf/eecs489/tree/master/Discussion/discussion3) helpful.

*Note: A good resource to remind you of socket programming is [Beej's Guide to Network Programming Using Internet Sockets](http://beej.us/guide/bgnet/output/html/multipage/index.html).*

### Throughput Calculation

Your proxy should estimate each stream's throughput once per chunk. Note the start time of each chunk request when your proxy receives a request from the player and save another timestamp when you have finished receiving the chunk from the server. Given the size of the chunk, you can now compute the throughput by dividing chunk size by time window.

Each video is a sequence of chunks. To smooth your throughput estimation, you should use an exponentially-weighted moving average (EWMA). Every time you make a new measurement (as outlined above), update your current throughput estimate as follows:

`T_cur = alpha * T_new + (1 - alpha) * T_cur`

The constant `0 ≤ alpha ≤ 1` controls the tradeoff between a smooth throughput estimate (`alpha` closer to 0) and one that reacts quickly to changes (`alpha` closer to 1). You will control `alpha` via a command line argument. When a new stream starts, set `T_cur` to the lowest available bitrate for that video.

### Choosing a Bitrate

Once your proxy has calculated the connection's current throughput, it should select the highest offered bitrate the connection can support. For this project, we say a connection can support a bitrate if the average throughput is at least 1.5 times the bitrate. For example, before your proxy should request chunks encoded at 1000 Kbps, its current throughput estimate should be at least 1.5 Mbps.

Your proxy should learn which bitrates are available for a given video by parsing the manifest file (the ".f4m" initially requested at the beginning of the stream). The manifest is encoded in XML; each encoding of the video is described by a `<media>` element, whose bitrate attribute you should find.

Your proxy replaces each chunk request with a request for the same chunk at the selected bitrate (in Kbps) by modifying the HTTP request’s `Request-URI`. Video chunk URIs are structured as follows:

`/path/to/video/<bitrate>Seg<num>-Frag<num>`

For example, suppose the player requests fragment 3 of chunk 2 of the video `big_buck_bunny.f4m` at 500 Kbps:

`/path/to/video/500Seg2-Frag3`

To switch to a higher bitrate, e.g., 1000 Kbps, the proxy should modify the URI like this:

`/path/to/video/1000Seg2-Frag3`

**IMPORTANT:** When the video player requests `big_buck_bunny.f4m`, you should instead return `big_buck_bunny_nolist.f4m`. This file does not list the available bitrates, preventing the video player from attempting its own bitrate adaptation. You proxy should, however, fetch `big_buck_bunny.f4m` for itself (i.e., don’t return it to the client) so you can parse the list of available encodings as described above. Your proxy should keep this list of available bitrates in a global container (not on a connection by connection basis).

### Running `miProxy`
To operate `miProxy`, it should be invoked as follows:

`./miProxy <log> <alpha> <listen-port> <dns-ip> <dns-port> [<www-ip>]`

* `log` The file path to which you should log the messages as described below.
* `alpha` A float in the range [0, 1]. Uses this as the coefficient in your EWMA throughput estimate.
* `listen-port` The TCP port your proxy should listen on for accepting connections from your browser.
* `dns-ip` IP address of the DNS server.
* `dns-port` Port number DNS server listens on.
* `www-ip` Your proxy should accept an optional argument specifying the IP address of the web server from which it should request video chunks. If this argument is not present, your proxy should obtain the web server's IP address by querying your DNS server for the name `video.cse.umich.edu`.

###Logging
`miProxy` must create a log of its activity in a very particular format. After each request, it should append the following line to the log:

`<duration> <tput> <avg-tput> <bitrate> <server-ip> <chunkname>`

* `duration` A floating point number representing the number of seconds it took to download this chunk from the server to the proxy.
* `tput` The throughput you measured for the current chunk in Kbps.
* `avg-tput` Your current EWMA throughput estimate in Kbps.
* `bitrate` The bitrate your proxy requested for this chunk in Kbps.
* `server-ip` The IP address of the server to which the proxy forwarded this request.
* `chunkname` The name of the file your proxy requested from the server (that is, the modified file name in the modified HTTP GET message).

### Testing
To play a video through your proxy, you can simply launch a local instance of the Apache server, launch Firefox (see above), and point the browser on your VM to the URL `http://localhost:<listen-port>/index.html`.


<a name="part2"></a>
## Part 2: DNS Load Balancing

To spread the load of serving videos among a group of servers, most CDNs perform some kind of load balancing. A common technique is to configure the CDN's authoritative DNS server to resolve a single domain name to one out of a set of IP addresses belonging to replicated content servers. The DNS server can use various strategies to spread the load, e.g., round-robin, shortest geographic distance, or current server load (which requires servers to periodically report their statuses to the DNS server).

You will write a simple DNS server that implements load balancing in two different ways: round-robin and geographic distance. In order for you proxy to be able to query your DNS server, you must also write an accompanying DNS resolution library. The two pieces should communicate using the DNS classes we provide (`DNSHeader.h`, `DNSQuestion.h`, and `DNSRecord.h`). You can read more about what each of the fields in these classes represents [here](http://www.freesoft.org/CIE/RFC/1035/39.htm). To make your life easier:

* `AA` Set this to 0 in requests, 1 in responses.

* `RD` Set this to 0 in all messages.

* `RA` Set this to 0 in all messages.

* `Z` Set this to 0 in all messages.

* `NSCOUNT` Set this to 0 in all messages.

* `ARCOUNT` Set this to 0 in all messages.

* `QTYPE` Set this to 1 in all requests (asking for an A record).

* `QCLASS` Set this to 1 in all requests (asking for an IP address).

* `TYPE` Set this to 1 in all responses (returning an A record).

* `CLASS` Set this to 1 in all responses (returning an IP address).

* `TTL` Set this to 0 in all responses (no caching).

### Round-Robin Load Balancer
One of the ways you will implement `nameserver` is as a simple round-robin based DNS load balancer. It should take as input a list of video server IP addresses on the command line; it responds to each request to resolve the name `video.cse.umich.edu` by returning the next IP address in the list, cycling back to the beginning when the list is exhausted.

`nameserver` will bind to an IP address and port specified as command line arguments. It responds *only* to requests for `video.cse.umich.edu`; any other requests should generate a response with `RCODE` 3.

### Geographic Distance Load Balancer
Next you’ll make your DNS server somewhat more sophisticated. Your load balancer must return the closest video server to the client based on the proxy’s IP address. In the real world, this would be done by querying a database mapping IP prefixes to geographic locations. For your implementation, however, you will be given information in a text file about the entire state of the network, and your server will have to return to a given client its closest geographic server.

The text file will be represented in the following way:
```
NUM_NODES: <number of hosts and switches in the network>
<host_id> <CLIENT|SWITCH|SERVER> <IP address|NO_IP>
(repeats NUM_NODES - 1 times)
NUM_LINKS: <number of links in the network>
<origin_id> <destination_id> <cost>
(repeats NUM_LINKS - 1 times)
```

<img src="link-cost.PNG" title="Video CDN in the wild" alt="" width="400" height="155"/>

As an example, the network shown above will have the following text file:
```
NUM_NODES: 6
0 CLIENT 10.0.0.1
1 CLIENT 10.0.0.2
2 SWITCH NO_IP
3 SWITCH NO_IP
4 SERVER 10.0.0.3
5 SERVER 10.0.0.4
NUM_LINKS: 5
0 2 1
1 2 1
2 3 1
3 4 6
3 5 1
```

To operate `nameserver`, it should be invoked as follows:

`./nameserver <log> <port> <geography_based> <servers>`

* `log` The file path to which you should log the messages as described below.
* `port` The port on which your server should listen.
* `geography_based` An integer that will either be 0 or 1. If it is 0, use the round-robin load balancing scheme, otherwise implement the distance based scheme.
* `servers` A text file containing a list of IP addresses, one per line, belonging to content servers if geography_based is 0. Otherwise it will be a text file describing the network topology as explained above.

####Logging
Your DNS server must log its activity in a specific format. For each valid DNS query it services, it should append the following line to the log:

`<client-ip> <query-name> <response-ip>`

* `client-ip` The IP address of the client who sent the query.
* `query-name` The hostname the client is trying to resolve.
* `response-ip` The IP address you return in response.

<a name="submission-instr"></a>
## Submission Instructions

You git repository must include the following:

* `Makefile`(s) to compile `miProxy` and `nameserver`
* The source code for `miProxy`: all source files for `miProxy` should be in a folder called `miProxy`
* The source code for `nameserver`: all source files for `nameserver` should be in a folder called `nameserver`
* A `README` file with the names and umich uniqnames of the group members. Also specify in this `README` if you choose to use any late days for this project.

## Acknowledgements
This programming assignment is based on Peter Steenkiste's Project 3 from CMU CS 15-441: Computer Networks.

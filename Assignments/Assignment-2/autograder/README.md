About the Autograder
-----------
This autograder is used for the students to evaluate Assignment 2. You should run the autograder inside the virtual machine you write your Assignment 2. We enabled a few global configurations in firefox for the autograder to work properly. So be sure to use the correct VM we provide in the Assignment 2 spec. The same VM will be used when you grade your code.

Note in this autograder, we only release a (small) subset of the entire test set. This is to give you a chance to verify your output format is correct, and you follow the spec to implement the basic behavior of the proxy server and DNS server. We encourage you to come up with your only test cases to fully test your code. Passing all the tests in this autograder does not guarantee a high final Assignment 2 grade.

The autograder consists of 2 binary files: `a2_auto` and `queryDNS`. The autograder binary is `a2_auto` and it is dependent on `queryDNS` (a client utility). Please make sure you place them under the same directory.

Running the Autograder
-----------

The autograder should be run as root. Like the autograder for Assignment one, you want to run it inside your vm but oustide the Mininet enviroment and there shouldn't be any Mininet instance running at the same time. You need to pass in the path to your **Assignment 2 repo**, under which `miProxy` and `nameserver` directories can be directly found (not under a few layers of subdirectories).
Directly under `miProxy` and `nameserver` directories, there should be a separate Makefile to compile your proxy server and nameserver.
As usual, your Makefile need to do `make` and `make clean` correctly.
Say you have everything ready in your repo, and you have changed directory to where the autograder is at. You can now run:

```bash
sudo ./a2_auto -d </path/to/your/repo>
```

When running the autograder, firefox and apache server as well as your proxy and DNS server will be launched. **You should not interfere with any of the processes.** For example, do not touch the browser (pause the video, refresh the video, close the browser, drag the video progress bar, etc) when the autograder is running.

If everything goes well, you will see something like the following printed out to screen (after some waiting time, of course):

```
Testing directory: ../nitish_assignment2/
###Complie succeeded.
make: Entering directory `/media/sf_EECS489/eecs489_p2_auto/nitish_assignment2/miProxy'
g++ -g -Wall -std=c++11 -o miProxy miProxy.cpp utils.cpp Connection.cpp ConnectionList.cpp
make: Leaving directory `/media/sf_EECS489/eecs489_p2_auto/nitish_assignment2/miProxy'

###Complie succeeded.
make: Entering directory `/media/sf_EECS489/eecs489_p2_auto/nitish_assignment2/nameserver'
g++ -g -Wall -std=c++11 -o nameserver nameserver.cpp NS.cpp GraphNode.cpp PQNode.cpp
make: Leaving directory `/media/sf_EECS489/eecs489_p2_auto/nitish_assignment2/nameserver'


###Start proxy server test.

Test (1) passed.

###Start DNS server test.

Test (2) passed.

Test (3) passed.

###Start intergration test.

Test (4) passed.

###[SUMMARY]: PASSED 4 out of 4 tests.

```

If you do not pass some of the test cases, you will see some hints (incorrect output, segmentation fault, etc) on why they failed.

There are other options you can pick, such as using a custom port instead of the default port picked by the autograder (you should pick a valid one), writing the autograder results to a log file named based on the date and time you lanuch it, or pick a custom name for the log file. Launch the autograder with `-h` option to see the details.

Though we have been careful when writing the autograder, you may still find your code cause some unexpected behaviors of the autograder. In those rare cases, you should contact the GSIs for further assistance.

Running `queryDNS`
----------------------

 `queryDNS` sends DNS query to `nameserver` (just like a `miProxy` does), and output the reponse from DNS server. So you can test your `nameserver` using `queryDNS` without `miProxy`.

 The command line to use `queryDNS` is:
 ```bash
<path to the binary>/queryDNS <IP of nameserver> <port of nameserver>
 ```

### Testing Round-Robin Load Balancer ###

For instance, start your `nameserver` using
```bash
<path to the binary>/nameserver log.txt 5001 0 sample_round_robin.txt
```
and repeatedly run `queryDNS` using
```bash
<path to the binary>/queryDNS localhost 5001
 ```

If everything goes well, you should get responses like `10.0.0.1`, `10.0.0.2` and `10.0.0.3`.

Note that the `queryDNS` is implemented according to serialization/deserialization format on our spec/piazza. So if your `nameserver` can't communicate with `queryDNS`, check your serialization/deserialization (especially Host to Network Byte Order translation etc.).

### Testing Geographic Distance Load Balancer ###
You can use mininet to instantiate a topology, and start `queryDNS` in the host where you were going to run `miProxy` initially.

Note that you should not use `localhost` to test Geographic Distance Load Balancer, because the DNS response is dependent on proxy’s IP address (in this case `queryDNS`'s IP address).

You want to test your `nameserver` with topologies that contains redundant paths.
Note that you don't need the topology for mininet and `nameserver`'s input file to match each other, because we are only testing the `nameserver` here.
Using mininet here is just for assigning the corresponding IP addresses (i.e., mininet provides a Layer-2, with connectivity and IP address, hence upper layers don't care about the actual topology underneath. This is why it is OK to have unmatched topologies).

If you have difficulties making mininet work with redundant paths, try a simpler topology for mininet, but remember to match the IP addresses.


### IMPORTANT ###

`queryDNS` is only a utility, not a test case.
You still have to come up with your own test cases and do rigorous testing.

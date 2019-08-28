# EECS 489: Computer Networks (F’19)

## Administrivia
 - Catalog Number: 29083
 - Lectures: 1109 FXB, MW: 4:00 PM – 5:30 PM
 - Discussion 1: 2150 DOW, F 9:30 AM – 10:30 AM
 - Discussion 2: 1014 DOW, Th 5:00 PM – 6:00 PM
 - Discussion 3: 1014 DOW, F 12:30 PM – 1:30 PM

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | 4820 BBB, W: 2:00 PM - 4:00 PM and by appt.
| Leonard Lin (yklin) | GSI | 4917 BBB, F: 10:00 PM - 12:00 PM |
| Joseph Buiteweg  | GSI | TBA |

### Piazza
All communication regarding this course must be via [Piazza](https://piazza.com/umich/fall2019/eecs489/). 
This includes questions, discussions, announcements, as well as private messages.

## Course Description
EECS 489 takes a top-down approach to explore how networks operate and how network applications are written. 
We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the *application layer*.
We explore how these applications transfer data between their components and end users over the Internet using *transport layer* protocols such as TCP and UDP.
We go deeper to understand what keeps the transport layer running (hint: the *network layer* routes packets for them); specifically, we look at how packets are routed and how routers work.
Finally, we dive one more layer down to understand how the *link layer* transfer packets using Ethernet.
In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks and software-defined networking (SDN). 

From a practical point of view, we learn what sockets are and how to use them. 
And we write code. 
We write code to implement various protocols, to build client-server applications, HTTP proxies, and video distribution applications, and to learn how to use SDNs.

### Prerequisite

The working prerequisite for this course is EECS 281 (Data Structures and Algorithms) even though officially it is EECS 482 (Operating Systems). 
The current curriculum of this course does not assume or require any prior knowledge of EECS 482.
Nonetheless, you must have a good working knowledge of C/C++ and Unix family of operating systems.

### Optional Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2016. ISBN 978-0133594140.

## Tentative Schedule

| Week of  | Monday | Wednesday | Optional Readings | Assignments
|:---------|:------:|:---------:|:------------------|:----------:
| 09/02/19 | **No Class** | [Introduction](Slides/090419.pptx) | 
| 09/09/19 | Overview | Protocol Layering | 1.1, 1.3, 1.4, 1.5 | A1 Out
| 09/16/19 | HTTP and the Web | DNS and CDN | 2.2, 2.4
| 09/23/19 | Video Streaming and Cloud Systems | Transport Layer | 2.6, 3.1, 3.2, 3.3, 3.4 | A1 Due
| 09/30/19 | TCP Basics | **No Class** | 3.5 | A2 Out
| 10/07/19 | Flow and Congestion Control | More Congestion Control | 3.6, 3.7
| 10/14/19 | **No Class** | Network Layer and IP | 4.1, 4.3.1, 4.3.2, 4.3.5
| 10/21/19 | Midterm Review | **MIDTERM** <br> **TBA** | | A2 Due<br>A3 Out
| 10/28/19 | IP Routers | Routing Fundamentals | 4.2, 5.1 | 
| 11/04/19 | Routing Algorithms | IP Addressing and Inter-AS Routing | 4.3.3, 5.2, 5.3
| 11/11/19 | BGP | SDN | 4.4, 5.4, 5.5 | A3 Due
| 11/18/19 | Link Layer | Switched LAN | 6.1, 6.3, 6.4 | A4 Out
| 11/25/19 | Datacenter Networks | **No Class** | 6.6
| 12/02/19 | Networking in Datacenters | Wireless | 6.6, 7.1, 7.2, 7.3
| 12/09/19 | Final Review | **No Class** | | A4 Due
| 12/16/19 | **FINAL <br> THURSDAY 12/19/19 <br> 1:30 PM - 3:30 PM <br> TBA** | | | 

## Policies

### Assignments
Four assignments will be assigned during the semester; the first one will be done individually and the rest will be in groups.
Visit [this page](Assignments) for detailed policies on assignments (including late submission policies) as well as the assignments themselves. 

### Exams
There will be two exams during the semester: a midterm exam and the final exam. 
You are expected to take both exams at the scheduled times. 

If you miss an exam for reasons other than a documented medical or personal emergency, you will receive a zero for that exam. 
If you anticipate a conflict with an exam time, talk to the instructor **at least one month** before the exam date. 
Exam dates are given at the beginning of the semester so you can avoid scheduling job interviews or other commitments on those days. 
Outside commitments are not considered a valid reason for missing an exam.

### Attendance and Discussion Sections
You are expected to attend lecture regularly and to be at your discussion section weekly. 
Discussion section meetings will typically involve active participation by discussion, group exercises, or question-and-answer sessions.

## Grading
Final grades will be based on the total points earned on the assignments and exams. 
You must average a passing grade on the exams to receive a passing grade for the class. 
Factors such as class participation may be used to adjust your final grade, especially if it falls on a borderline. 
The tentative point breakdown is:

|              | Allocation 
| -------------| ----------:
| Assignment 1 |  5%        
| Assignment 2 | 15%        
| Assignment 3 | 15%        
| Assignment 4 | 15%        
| Midterm Exam | 25%        
| Final Exam   | 25%        

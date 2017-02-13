# EECS 489: Computer Networks (W’17)

## Administrivia
 - Catalog Number: 10671
 - Lectures: 133 CHRYS, MW: 12:00 PM – 1:30 PM
 - Discussion 1: 1014 DOW, W 4:30 PM – 5:30 PM
 - Discussion 2: 1018 DOW, F 9:30 AM – 10:30 AM

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | 4820 BBB, W 2:00 PM - 4:00 PM and by appt.
| Nitish Paradkar (nitishp) | GSI | BBB Learning Center, T 2:00 PM - 4:00 PM |

### Piazza
All communication regarding this course must be via [Piazza](https://piazza.com/umich/winter2017/eecs489/). 
This includes questions, discussions, announcements, as well as private messages.

## Course Description
EECS 489 takes a top-down approach to explore how networks operate and how network applications are written. 
We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the *application layer*.
We explore how these applications transfer data between their components and end users over the Internet using *transport layer* protocols such as TCP and UDP.
We go deeper to understand what keeps the transport layer running (hint: the *network layer* routes packets for them); specifically, we look at how packets are routed and how routers work.
We dive one more layer down to understand how the *link layer* transfer packets using Ethernet.
In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art in datacenter networks, software-defined networking (SDNs), wireless and mobile networks, and network security. 

From a practical point of view, we learn what sockets are and how to use them. 
And we write code. 
We write code to implement various protocols, to build client-server applications, HTTP proxies, and video distribution applications, and to learn how to use SDNs.

### Prerequisite

The **mandatory** prerequisite for this course is EECS 482 (Introduction to Operating Systems). 
You must also have a good working knowledge of C/C++ and Unix family of operating systems.

### Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2012. ISBN 978-0133594140.

## Tentative Schedule

| Week of  | Monday | Wednesday | Readings | Assignments
|:---------|:------:|:---------:|:---------|:----------:
| 01/02/17 | **No Class** | [Introduction](Slides/010417.pptx) | 
| 01/09/17 | [Overview](Slides/010917.pptx) | [Protocol Layering](Slides/011117.pptx) | 1.1, 1.3, 1.4, 1.5 | A1 Out
| 01/16/17 | **No Class** | [HTTP and the Web](Slides/011817.pptx) | 2.2
| 01/23/17 | [DNS and CDN](Slides/012317.pptx) | [Video Streaming and Cloud Systems](Slides/012517.pptx) | 2.4, 2.6 | A1 Due
| 01/30/17 | [Transport Layer](Slides/013017.pptx) | [TCP Basics](Slides/020117.pptx) | 3.1, 3.2, 3.3, 3.4, 3.5 | A2 Out
| 02/06/17 | [Flow and Congestion Control](Slides/020617.pptx) | [More Congestion Control](Slides/020817.pptx) | 3.6, 3.7
| 02/13/17 | [Network Layer and IP](Slides/021317.pptx) | IP Routers | 4.1, 4.2, 4.3
| 02/20/17 | Midterm Review | **MIDTERM** <br> Regular time/location | | A2 Due<br>A3 Out
| 02/27/17 | **No Class** | **No Class** |
| 03/06/17 | Routing Algorithms | IP Addressing and Inter-AS Routing | 5.1, 5.2, 5.3
| 03/13/17 | BGP | Link Layer 1 | 
| 03/20/17 | Link Layer 2 | Wireless / Mobile | | A3 Due<br>A4 Out
| 03/27/17 | Datacenters 1 | Datacenters 2 |
| 04/03/17 | Security 1 | Security 2 | 
| 04/10/17 | SDN 1 |  SDN 2 | 
| 04/17/17 | Final Review | **FINAL** <br> Thursday 04/20/17 <br> 1:30 PM - 3:30 PM | | A4 Due

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
| Midterm Exam | 24%        
| Final Exam   | 26%        

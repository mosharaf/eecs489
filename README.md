# EECS 489: Computer Networks (F’18)

## Administrivia
 - Catalog Number: 31839
 - Lectures: 1109 FXB, MW: 4:30 PM – 6:00 PM
 - Discussion 1: 2150 DOW, F 9:30 AM – 10:30 AM
 - Discussion 2: 1014 DOW, Th 5:00 PM – 6:00 PM

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | 4820 BBB, W: 2:00 PM - 4:00 PM and by appt.
| Jie You (jieyou) | GSI | 1637 BBB, F: 10:30 AM - 12:30 PM |
| Yiwen Zhang (yiwenzhg) | GSI | 1637 BBB, Tu: 4:00 PM - 6:00 PM |

### Piazza
All communication regarding this course must be via [Piazza](https://piazza.com/umich/fall2018/eecs489/). 
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

The prerequisite for this course is EECS 281 (Data Structures and Algorithms). 
You must also have a good working knowledge of C/C++ and Unix family of operating systems.

### Optional Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2016. ISBN 978-0133594140.

## Tentative Schedule

| Week of  | Monday | Wednesday | Optional Readings | Assignments
|:---------|:------:|:---------:|:------------------|:----------:
| 09/03/18 | **No Class** | [Introduction](Slides/090518.pptx) | 
| 09/10/18 | [Overview](Slides/091018.pptx) | [Protocol Layering](Slides/091218.pptx) | 1.1, 1.3, 1.4, 1.5 | A1 Out
| 09/17/18 | [HTTP and the Web](Slides/091718.pptx) | [DNS and CDN](Slides/091918.pptx) | 2.2, 2.4
| 09/24/18 | [Video Streaming and Cloud Systems](Slides/092418.pptx) | [Transport Layer](Slides/092618.pptx) | 2.6, 3.1, 3.2, 3.3, 3.4 | A1 Due
| 10/01/18 | [TCP Basics](Slides/100118.pptx) | [Flow and Congestion Control](Slides/100318.pptx) <br> (**LOCATION: Stamps**) | 3.5, 3.6 | A2 Out
| 10/08/18 | **No Class** | [More Congestion Control](Slides/101018.pptx) | 3.7
| 10/15/18 | **No Class** | [Network Layer and IP](Slides/101718.pptx) | 4.1, 4.3.1, 4.3.2, 4.3.5
| 10/22/18 | [Midterm Review](Slides/102218.pptx) | **MIDTERM** <br> Regular time/location | | A2 Due<br>A3 Out
| 10/29/18 | [IP Routers](Slides/102918.pptx) | [Routing Fundamentals](Slides/103118.pptx) | 4.2, 5.1 | 
| 11/05/18 | Routing Algorithms | IP Addressing and Inter-AS Routing | 4.3.3, 5.2, 5.3
| 11/12/18 | BGP | SDN | 4.4, 5.4, 5.5 | A3 Due
| 11/19/18 | Link Layer | **No Class** | 6.1, 6.3, 6.4.2 | A4 Out
| 11/26/18 | Switched LAN | Datacenter Networks | 6.4, 6.6
| 12/03/18 | Networking in Datacenters | Wireless | 6.6, 7.1, 7.2, 7.3
| 12/10/18 | Final Review | **No Class** | | A4 Due
| 12/17/18 | **FINAL <br> MONDAY 12/17/18 <br> 10:30 AM - 12:30 PM <br> TBA** | | | 

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

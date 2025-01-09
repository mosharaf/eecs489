# EECS 489: Computer Networks (W’25)

## Administrivia
 - Catalog Number: 28919
 - Lectures (Recorded): 1013 DOW, MW: 10:30 AM – 12:00 PM
 - Discussion 002: 2147 GGBL, Th 4:30 PM – 5:30 PM
 - Discussion 001: 3150 DOW, F 9:30 AM – 10:30 AM
 - Discussion 003 (Recorded): 1311 EECS, F 12:30 PM – 1:30 PM
 - [Recordings](https://umich.instructure.com/courses/730716/external_tools/1262)

You can add the course Google Calendar [here](https://calendar.google.com/calendar/u/0?cid=Y19iMDk0ZGE2ZjE5YmU1NDAyZTk3Y2EwY2I2MDE2Y2RjOWJhZWIyYWRlZjRkZTRjMjc3MDRmZDJjN2E3NTc4M2VjQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20), which will be updated with all lectures, discussions, and office hours. 

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | 4820 BBB, Th 2:45 PM - 3:45 PM
| Efe Akinci (efea) | GSI | BBB Learning Center Table 1, Mon 3 PM - 5 PM
| Alexander De La Iglesia (alexdela) | GSI | BBB Atrium, Mon 12 PM - 1 PM <br> BBB Learning Center Table 1, Wed 12 PM - 1 PM 
| Aditya Singhvi (singhvi) | GSI | BBB Learning Center Table 1, Tues 10AM - 12PM

Office hours will use a queue if demand is high. You can sign up on the queue [here](https://eecsoh.efeakinci.com/queues/eecs-489-bbb-office-hours). 

In addition to the listed office hours here, GSIs will add more office hours as project deadlines near. These office hours can be found on the [course Google Calendar](https://calendar.google.com/calendar/u/0?cid=Y19iMDk0ZGE2ZjE5YmU1NDAyZTk3Y2EwY2I2MDE2Y2RjOWJhZWIyYWRlZjRkZTRjMjc3MDRmZDJjN2E3NTc4M2VjQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20). 

### Ed
All communication regarding this course must be via [Ed](https://edstem.org/us/join/jwtp2b). 
This includes questions, discussions, announcements, as well as private messages. 

## Course Description
EECS 489 takes a top-down approach to explore how networks operate and how network applications are written. 
We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the *application layer*.
We explore how these applications transfer data between their components and end users over the Internet using *transport layer* protocols such as TCP and UDP.
We go deeper to understand what keeps the transport layer running (hint: the *network layer* routes packets for them); specifically, we look at how packets are routed and how routers work.
Finally, we dive one more layer down to understand how the *link layer* transfer packets using Ethernet.
In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks, wireless networks, software-defined networking (SDN), and programmable networks. 

From a practical point of view, we learn what sockets are and how to use them. 
And we write code. 
We write code to implement various protocols, to build client-server applications, HTTP proxies, and video distribution applications, and to learn how to use programmable networks.

### Prerequisite

The enforced prerequisite for this course is EECS 281 (Data Structures and Algorithms) and EECS 370 (Introduction to Computer Organization). 

This course does not assume or require any prior knowledge of EECS 482.
Nonetheless, you must have a good working knowledge of C/C++ and Unix family of operating systems.

### Optional Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2016. ISBN 978-0133594140.
- Peterson and Davie, [Computer Networks: A Systems Approach](https://book.systemsapproach.org/)

## Tentative Schedule

| Week of  | Monday | Wednesday | K & R | P & D | Discussion | Assignments |
|:---------|:------:|:---------:|:------|:------|:----------:|:-----------:|
| 01/06/24 | **No Class** | [Introduction and Overview](Slides/010825.pdf) | 1.1, 1.3, 1.4 | 1.1, 1.2, 1.5 | No Discussion | A1 Out
| 01/13/24 | Protocol Layering | HTTP and the Web | 1.5, 2.2 | 1.3, 9.1.2 | Sockets, A1 Intro
| 01/20/24 | **No Class** | DNS and CDN | 2.4 | 9.3.1 | Performance Metrics, HTTP, Byte Order
| 01/27/24 | Video Streaming and Cloud Systems | Transport Layer | 2.6, 3.1-3.4 | 9.4.3, 5.1 | A1 Recap, A2 Overview, DNS | A1 Due<br>A2 Out
| 02/03/24 | TCP Basics | Flow and Congestion Control | 3.5, 3.6 | 5.2, 6 | Video Streaming, Reliable Transport
| 02/10/24 | More Congestion Control | **No Class** | 3.7 | 6.3 | TCP, IP
| 02/17/24 | Network Layer and IP | *Midterm Review* | 4.1, 4.3.1, 4.3.2, 4.3.5 | 3.3 | FA24 Midterm Exam Review | A2 Due
| 02/24/24 | **MIDTERM (TBA)** | **No Class** | | | No Discussion | A3 Out
| 03/03/24 | **No Class** | **No Class** | | | No Discussion
| 03/10/24 | IP Routers | Routing Fundamentals | 4.2, 5.1 | 3.5.2, 3.4 | A2 Recap, A3 Overview, Routing Data Plane
| 03/17/24 | Intra-AS Routing | IP Addressing and Inter-AS Routing | 4.3.3, 5.2, 5.3 | 3.4, 3.3 | Intra-AS Routing, Poisioned Reverse, General Programming Advice
| 03/24/24 | BGP | Software-Defined Networking | 4.4, 5.4, 5.5 | 4.1, 3.5.3 | A4 Overview, ARP, A4 Exercises | A3 Due<br>A4 Out
| 03/31/24 | **No Class** | Link Layer | 6.1, 6.3 | 2.6 | Wireshark Tutorial, Modern C++
| 04/07/24 | Switched LAN | Wireless Networking | 6.4, 6.4.2, 7.1-7.3 | 3.2, 2.7 | Link Layer
| 04/14/24 | Datacenter Networking | *Final Review* | 6.6 | 6.4 | FA24 Final Exam Review
| 04/21/24 | **No Class** | **FINAL (TBA)** | | | No Discussion | A4 Due

## Policies

### Assignments
Four assignments will be assigned during the semester; the first one will be done individually and the rest will be in groups.
Visit [this page](Assignments) for detailed policies on assignments (including late submission policies) as well as the assignments themselves. 

### Exams
There will be two exams during the semester: a midterm exam and the final exam. Both exams will be held in-person. You are expected to take both exams at the scheduled times. 

If you miss an exam for reasons other than a documented medical or personal emergency, you will receive a zero for that exam. 
If you anticipate a conflict with an exam time, talk to the instructor **at least one month** before the exam date. 
Exam dates are given at the beginning of the semester so you can avoid scheduling job interviews or other commitments on those days. 
Outside commitments are not considered a valid reason for missing an exam.

### Attendance and Discussion Sections
You are expected to attend lecture regularly and to be at a discussion section weekly. You may attend any discussion section; all three sections in a given week will be taught by the same instructor and cover the same content. 

Discussion section meetings will typically involve active participation by discussion, group exercises, or question-and-answer sessions.

### Commitment to Equal Opportunity 
As indicated in the [General Standards of Conduct for Engineering Students](https://bulletin.engin.umich.edu/rules/#generalstandardsofconductforengineeringstudents), we are committed to a policy of equal opportunity. 
We ask that all students treat each other with respect. 
Please feel free to contact us with any problems, concerns, or suggestions.

### Lecture Recordings

Course lectures will be recorded and made available via the lecture capturing site. 

Students may not record or distribute any class activity without written permission from the instructor, except as necessary as part of approved accommodations for students with disabilities. 
Any approved recordings may only be used for the student's own private use.

### Quizzes
Each lecture has an associated quiz that will be made available sometime after the lecture and will be available for at least 48 hours. 

*Quizzes are not graded for correctness*. They are for self-evaluating your understanding of the material. 
Completing all quizzes will result in a total of 2% bonus grade on top of the entire grade.

## Grading
Final grades will be based on the total points earned on the assignments and exams. 
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
| **Total**    |100%
| Quiz (Bonus) |  2%  

# EECS 489: Computer Networks (F’21)

## Administrivia
 - Catalog Number: 26207 (In-person) & 38527 (Remote)
 - Lectures: 2505 GBL (Recorded), MW: 3:00 PM – 4:30 PM
 - Discussion 1: 2150 DOW, F 9:30 AM – 10:30 AM
 - Discussion 2: 1005 DOW, Th 5:00 PM – 6:00 PM
 - Discussion 3: 1014 DOW, F 12:30 PM – 1:30 PM

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | [W: 2:00 PM - 2:50 PM](https://officehours.it.umich.edu/queue/421) and by appt.
| Yinwei Dai | GSI | [F: 1:00 PM - 3:00 PM](https://officehours.it.umich.edu/queue/907)
| Jiaxing Yang | GSI | TBA

### Piazza
All communication regarding this course must be via [Piazza](https://piazza.com/umich/fall2021/eecs489). 
This includes questions, discussions, announcements, as well as private messages.

## Course Description
EECS 489 takes a top-down approach to explore how networks operate and how network applications are written. 
We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the *application layer*.
We explore how these applications transfer data between their components and end users over the Internet using *transport layer* protocols such as TCP and UDP.
We go deeper to understand what keeps the transport layer running (hint: the *network layer* routes packets for them); specifically, we look at how packets are routed and how routers work.
Finally, we dive one more layer down to understand how the *link layer* transfer packets using Ethernet.
In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks, software-defined networking (SDN), and programmable networks. 

From a practical point of view, we learn what sockets are and how to use them. 
And we write code. 
We write code to implement various protocols, to build client-server applications, HTTP proxies, and video distribution applications, and to learn how to use programmable networks.

### Prerequisite

The enforced prerequisite for this course is EECS 281 (Data Structures and Algorithms) and EECS 370 (Introduction to Computer Organization). 
This course does not assume or require any prior knowledge of EECS 482.
Nonetheless, you must have a good working knowledge of C/C++ and Unix family of operating systems.

If needed, you can get an override by signing up [here](https://forms.gle/vaW6x4UsbjFvT6WP7).

### Optional Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2016. ISBN 978-0133594140.

## Tentative Schedule

| Week of  | Monday | Wednesday | Optional Readings | Assignments
|:---------|:------:|:---------:|:------------------|:----------:
| 08/30/20 | [Introduction and Overview](Slides/083021.pptx) | **No Class** | 1.1, 1.3, 1.4 | A1 Out
| 09/06/20 | **No Class** | Protocol Layering | 1.5
| 09/13/20 | HTTP and the Web | DNS and CDN | 2.2, 2.4
| 09/20/20 | Video Streaming and Cloud Systems | Transport Layer | 2.6, 3.1, 3.2, 3.3, 3.4 | A1 Due<br>A2 Out
| 09/27/20 | TCP Basics | Flow and Congestion Control | 3.5, 3.6
| 10/04/20 | More Congestion Control | Network Layer and IP | 3.7, 4.1, 4.3.1, 4.3.2, 4.3.5
| 10/11/20 | IP Routers | *Midterm Review* | 4.2
| 10/18/20 | **No Class** | **MIDTERM (90 Min; Online) <br> TBD <br>** |  | A2 Due<br>A3 Out
| 10/25/20 | Routing Fundamentals | Intra-AS Routing | 5.1, 5.2, 5.3
| 11/01/20 | IP Addressing and Inter-AS Routing | BGP | 4.3.3, 5.4
| 11/08/20 | Software-Defined Networking | **No Class** | 4.4, 5.5 | A3 Due<br>A4 Out
| 11/15/20 | Link Layer | Switched LAN | 6.1, 6.3, 6.4
| 11/22/20 | **No Class** | **No Class**
| 11/29/20 | Wireless Networking | Datacenter Networking | 6.6, 7.1, 7.2, 7.3
| 12/06/20 | *Final Review* | **No Class** | | A4 Due
| 12/20/20 | **FINAL (90 Min; Online) <br> 8AM**

## Policies

### Assignments
Four assignments will be assigned during the semester; the first one will be done individually and the rest will be in groups.
Visit [this page](Assignments) for detailed policies on assignments (including late submission policies) as well as the assignments themselves. 

### Exams
There will be two exams during the semester: a midterm exam and the final exam. 
Both exams will be **online**.
You are expected to take both exams at the scheduled times. 

If you miss an exam for reasons other than a documented medical or personal emergency, you will receive a zero for that exam. 
If you anticipate a conflict with an exam time, talk to the instructor **at least one month** before the exam date. 
Exam dates are given at the beginning of the semester so you can avoid scheduling job interviews or other commitments on those days. 
Outside commitments are not considered a valid reason for missing an exam.

### Attendance and Discussion Sections
You are expected to attend lecture regularly and to be at your discussion section weekly. 
Discussion section meetings will typically involve active participation by discussion, group exercises, or question-and-answer sessions.

### Commitment to Equal Opportunity 
As indicated in the [General Standards of Conduct for Engineering Students](https://bulletin.engin.umich.edu/rules/#generalstandardsofconductforengineeringstudents), we are committed to a policy of equal opportunity. 
We ask that all students treat each other with respect. 
Please feel free to contact us with any problems, concerns, or suggestions.

### Lecture Recordings

Course lectures may be audio/video recorded and made available to other students in this course. As part of your participation in this course, you may be recorded. If you do not wish to be recorded, please contact `eecs489-staff` the first week of class to discuss alternative arrangements.

Students may not record or distribute any class activity without written permission from the instructor, except as necessary as part of approved accommodations for students with disabilities. Any approved recordings may only be used for the student’s own private use.

### Quizzes
Each lecture has an associated quiz (available via canvas) that is made available sometime after the lecture and will be available for at least 48 hours. 

Quizzes are *not* graded for correctness; they are for self-evaluating your understanding of the material. 
However, completing each quiz will result in 0.1% bonus grade after the total grade has been calculated at the end of the semester (for a maximum of 2% bonus grade over 20 quizzes).

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

# EECS 489: Computer Networks (F’20)

## Administrivia
 - Catalog Number: 28220
 - Lectures: Live Online, MW: 3:30 PM – 5:00 PM
 - Discussion 1: Live Online, F 9:30 AM – 10:30 AM
 - Discussion 2: Live Online, Th 6:00 PM – 7:00 PM
 - Discussion 3: Live Online, F 12:30 PM – 1:30 PM

### Team

| Member (uniqname) | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Mosharaf Chowdhury](http://www.mosharaf.com/) (mosharaf) | Faculty | [W: 2:00 PM - 3:15 PM](https://officehours.it.umich.edu/queue/421) and by appt.
| Jie You | GSI | [T: 9:30 AM - 11:30 AM](https://officehours.it.umich.edu/queue/518)
| Joseph Buiteweg | GSI | [W: 12:00 PM - 2:00 PM](https://officehours.it.umich.edu/queue/510)

### Piazza
All communication regarding this course must be via [Piazza](https://piazza.com/umich/fall2020/eecs489). 
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

The enforced prerequisite for this course is EECS 281 (Data Structures and Algorithms) and EECS 370 (Introduction to Computer Organization) even though officially it is EECS 482 (Operating Systems). 
The current curriculum of this course does not assume or require any prior knowledge of EECS 482.
Nonetheless, you must have a good working knowledge of C/C++ and Unix family of operating systems.

If needed, you can get an override by signing up [here](https://forms.gle/vaW6x4UsbjFvT6WP7).

### Optional Textbook

- Kurose and Ross, Computer Networking: A Top-Down Approach, 7th. or Earlier Editions, Pearson, 2016. ISBN 978-0133594140.

## Tentative Schedule

| Week of  | Monday | Wednesday | Optional Readings | Assignments
|:---------|:------:|:---------:|:------------------|:----------:
| 08/31/20 | [Introduction and Overview](Slides/083120.pptx) | [Protocol Layering](Slides/090220.pptx) | 1.1, 1.3, 1.4, 1.5 | A1 Out
| 09/07/20 | **No Class** | [HTTP and the Web](Slides/090920.pptx) | 2.2 |
| 09/14/20 | [DNS and CDN](Slides/091420.pptx) | [Video Streaming and Cloud Systems](Slides/091620.pptx) | 2.4, 2.6
| 09/21/20 | [*Review 1*](Slides/092120.pptx) | [Transport Layer](Slides/092320.pptx) | 3.1, 3.2, 3.3, 3.4 | A1 Due<br>A2 Out
| 09/28/20 | [TCP Basics](Slides/092820.pptx) | [Flow and Congestion Control](Slides/093020.pptx) | 3.5, 3.6 | 
| 10/05/20 | [More Congestion Control](Slides/100520.pptx) | [Network Layer and IP](Slides/100720.pptx) | 3.7, 4.1, 4.3.1, 4.3.2, 4.3.5
| 10/12/20 | [IP Routers](Slides/101220.pptx) | [*Review 2*](Slides/101420.pptx) | 4.2
| 10/19/20 | **MIDTERM (90 Min) <br> 3:30PM EDT <br> and <br> 11:30PM EDT** <br> [Sign up](https://forms.gle/deP3Z6fENaLHJLrH9) | **No Class** |  | A2 Due<br>A3 Out
| 10/26/20 | [Routing Fundamentals](Slides/102620.pptx) | [Intra-AS Routing](Slides/102820.pptx) | 5.1, 5.2, 5.3 | 
| 11/02/20 | [IP Addressing and Inter-AS Routing](Slides/110220.pptx) | [BGP](Slides/110420.pptx) | 4.3.3, 5.4
| 11/09/20 | Software-Defined Networking | *Review 3* | 4.4, 5.5 | A3 Due<br>A4 Out
| 11/16/20 | Link Layer | Switched LAN | 6.1, 6.3, 6.4 | 
| 11/23/20 | **No Class** | **No Class** | 
| 11/30/20 | Datacenter Networking | Wireless Networking | 6.6, 7.1, 7.2, 7.3
| 12/07/20 | *Review 4* | **No Class** | | A4 Due
| 12/14/20 | **FINAL <br> Wednesday 12/16/20 <br> 8AM - 10AM** | | | 

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

### Commitment to Equal Opportunity 
As indicated in the [General Standards of Conduct for Engineering Students](https://bulletin.engin.umich.edu/rules/#generalstandardsofconductforengineeringstudents), we are committed to a policy of equal opportunity. 
We ask that all students treat each other with respect. 
Please feel free to contact us with any problems, concerns, or suggestions.

### Lecture Recordings

Course lectures may be audio/video recorded and made available to other students in this course. As part of your participation in this course, you may be recorded. If you do not wish to be recorded, please contact `eecs489-staff` the first week of class to discuss alternative arrangements.

Students may not record or distribute any class activity without written permission from the instructor, except as necessary as part of approved accommodations for students with disabilities. Any approved recordings may only be used for the student’s own private use.

### Quizzes
Each lecture has an associated quiz (available via canvas) that is made available sometime after the lecture and will be available for at least 48 hours. 

Quizzes are not graded for correctness; they are for self-evaluating your understanding of the material. 
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

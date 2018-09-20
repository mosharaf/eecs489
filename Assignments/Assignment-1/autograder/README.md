About the Autograder
-----------
This autograder is used for the students to evaluate the `iPerfer` written in Part 1 of the assignment. You should run the autograder inside the virtual machine (VM) we provide ([link here](https://drive.google.com/file/d/1JNOH995lIz453AMdkVPtnDaJ0Wx0Oe5u/view?usp=sharing)). Running it elsewhere is likely to produce bogus results. When we grade your `iPerfer`, we will run the autograder for everyone inside the VM.

Running the Autograder
-----------

The autograder should be run as root. You want to run it inside your vm but oustide the Mininet enviroment. To make it clear, the autograder starts mininet when testing. So you shouldn't call it inside your own Mininet enviroment. You need to at least pass in the root directory which holds your iPerfer source code and a corresponding Makefile.
To make it clear, your Makefile and `iPerfer` binary produced from the Makefile should be located directly under the directory you pass in, rather than under some subdirectories.
Feel free to write your Makefile whatever way you want, but remember it needs to compile your iPerfer with `make` and cleanup the `iPerfer` binary with `make clean`.
Say you have everything ready inside your /home/mininet/eecs489_a1 folder, and you have changed directory to where the autograder is at. You can now run:

```bash
sudo ./a1_auto -d /home/mininet/eecs489_a1
```

If everything goes well, you will see something like the following printed out to screen (after some waiting time, of course):

```
Testing directory: /users/yiwenzhg/eecs489-assignments/solutions/assignment1/
###Complie succeeded.

make: Entering directory '/users/yiwenzhg/eecs489-assignments/solutions/assignment1'
g++ -g -Wall -std=c++11 -o iPerfer iPerfer.cpp
make: Leaving directory '/users/yiwenzhg/eecs489-assignments/solutions/assignment1'


###Start error handling test.

Test (1) passed.


Test (2) passed.


###Start simple connection test.

Test (3) passed.


Test (4) passed.


Test (5) passed.


Test (6) passed.


Test (7) passed.


Test (8) passed.


Test (9) passed.


Test (10) passed.


###[SUMMARY]: PASSED 10 out of 10 tests.

```

If you do not pass some of the test cases, you will see some hints (incorrect output, timeout exception, etc) on why they failed.

There are other options you can pick, such as using a custom port instead of the default port picked by the autograder (you should pick a valid one), writing the autograder results to a log file named based on the date and time you lanuch it, or pick a custom name for the log file. Launch the autograder with `-h` option to see the details.

Though we have been careful when writing the autograder, you may still find your code cause some unexpected behaviors of the autograder. In those rare cases, you should contact the GSIs for further assistance.

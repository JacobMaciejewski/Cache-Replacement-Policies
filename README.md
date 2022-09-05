# Cache-Replacement-Policies
Implementation of popular memory management algorithms including LRU and Second Chance 💾

Modern computers have different types of memories, varying in size, retrieval speed and price. In order to get the most out of it, [Cache Algorithms](https://en.wikipedia.org/wiki/Cache_replacement_policies)
were invented. They optimize instructions that a computer program or a hardware-maintained structure can utilize in order to manage a cache of
information stored on the computer.</br>

**Caching** improves performance by keeping recent or often-used data items in memory locations that are faster
or computationally cheaper to access than normal memory stores. When the cache is full, the algorithm must choose which items to discard to make room 
for the new ones. We implement two of the most popular algorithms, namely:
* [Least Recently Used](https://www.educative.io/answers/what-is-the-least-recently-used-page-replacement-algorithm) - known as the **LRU** is a Greedy Algorithm where the page to be replaced
is least recently used. The idea is based on **Locality Of Reference**, stating that a page that has been unused for a great amount of time is more
likely to remain unused, ergo should be removed
* [Second Chance](https://www.geeksforgeeks.org/second-chance-or-clock-page-replacement-policy/) - the candidate pages for removal are considered in a
**Round Robin Matter**, and a page that has been accessed between consecutive considerations will not be replaced. The page replaced is the one that,
when considered in a round robin matter, has not been accessed since its last consideration

## Compilation & Execution:

In order to compile the source code, type: `make` </br>
In order to execute the program, type: `./p2 -f1 <First File> -a <Algorithm: LRU / Second Chance> -fn <Number Of Frames> -f2 <Second File> -fr <Lines Read Per File> -tr <Number Of Actions>`

After a successful simulation execution, the program prints the number of [Page Faults](https://en.wikipedia.org/wiki/Page_fault),
which in our case is equal to the number of new **Disk Reads**, as those are the result of a page missing in the cache memory. The total number of **Disk Writes**
executed throughout the simulation after memory cleanup (includes the **Dirty Files** remaining in the hashtables), and number of available pages, are printed as well.

### Further Information:

We include a readME PDF file that contains an extensive description of the project set up, the inner workings of the respective algorithms and my design choices.
A brief description of the contents of corresponding files is given. *This PDF is written in Greek!*

*Built as part of the course: Operational Systems , Winter of 2019. University of Athens, DiT.*

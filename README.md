### a LanDen Labs - JavaTree
Java Developer Tool


WebSite
[http://landenlabs.com](http://landenlabs.com)

Github
[https://github.com/landenlabs/javatree](https://github.com/landenlabs/javatree)

Sample Android class tree diagrams, tables and direct graphs
[http://landenlabs.com](http://landenlabs.com/android/classtree/classtree.html)

***
Parse Java source files and produce class relationship as HTML, GraphViz or Text file
***

Javatree help banner
<blockquote>
<pre>
javatree (v1.4)

Des: Generate Java class dependence tree (Dec 30 2017)
Use: Javatree [-+ntgxshjz] header_files...

<p>
Switches (*=default)(-=off, +=on):
  n  ; Show alphabetic class name list
* t  ; Show class dependency tree

<p>
Output format (single choice):
* g  ; Use graphics for tree connections
  x  ; Use (+|-) for tree connections
  s  ; Use spaces for tree connections
  h  ; Html tree connections (needs images 0.png, 1.png, 2.png, n.png)
  j  ; Java tree connections (needs dtree www.destroydrop.com/javascript/tree/)
  z  ; GraphViz (see https://graphviz.gitlab.io/)

<p>
Modifiers:
  Z              ; Split GraphViz by tree, use with -O
  N=nodesPerFile ; Split by nodes per file, use with -O
  O=outpath      ; Save output in file
  T=tabular      ; Tabular html 
  V=filePattern  ; Ignore files
  A=allClasses   ; Defaults to public
  F=full path    ; Defaults to relative

<p>
Examples (assumes java source code in directory src):
  javatree -t +n  src\*.java  ; *.java prevent recursion
  javatree -x  src > javaTree.txt
  javatree -h  src > javaTree.html
  javatree -h -T src > javaTable.html
  javatree -j  src > javaTreeWithJs.html
  
 <p>
  -V is case sensitive 
  javatree -z -Z -O=.\viz\ -V=*Test* -V=*Exception* src >directgraph.dot
  javatree -z -N=10 -O=.\viz\ -V=*Test* -V=*Exception* src >directgraph.dot

 </pre>
 </blockquote>
  
  
***
Example test script to generate reports using sample Java code
***
  
<blockquote>
<pre>
#!/bin/csh -f

\#
\#  Generate test reports
\#

javatree test       > reports/windows.txt
javatree -h test    >  reports/html.html
javatree -h -T test >  reports/tabular.html
javatree -x test    >  reports/text.txt
javatree -t +n test >  reports/list.txt
javatree -j test    > reports/tree.html
javatree -z test    > reports/directgraph.dot
</pre>
</blockquote>

***
Sample reports
***

        "\n  h  ; Html tree connections (needs images 0.png, 1.png, 2.png, n.png)"
            "\n  j  ; Java tree connections (needs dtree www.destroydrop.com/javascript/tree/)"
            "\n  z  ; GraphViz (see https://graphviz.gitlab.io/)"
            
            
### javatree -h test    >  reports/html.html
![ScreenShot](http://landenlabs.com/code/javatree/images/report-html.png)
The above html report needs several png images to correctly display the page.
![ScreenShot](http://landenlabs.com/code/javatree/reports/0.png)
![ScreenShot](http://landenlabs.com/code/javatree/reports/1.png)
![ScreenShot](http://landenlabs.com/code/javatree/reports/2.png)
![ScreenShot](http://landenlabs.com/code/javatree/reports/n.png)

### javatree -h -T test >  reports/tabular.html
![ScreenShot](http://landenlabs.com/code/javatree/images/report-tabular.png)

### javatree -x test    >  reports/text.txt
![ScreenShot](http://landenlabs.com/code/javatree/images/report-text.png)

### javatree -t +n test >  reports/list.txt
![ScreenShot](http://landenlabs.com/code/javatree/images/report-list.png)

### javatree -j test    > reports/tree.html
![ScreenShot](http://landenlabs.com/code/javatree/images/report-tree.png)

### javatree -z test    > reports/directgraph.dot
### neato -Tpng reports/directgraph.dot > images/directgraph.png
![ScreenShot](http://landenlabs.com/code/javatree/images/directgraph.png)


### Sample Android class tree diagrams, tables and direct graphs
[http://landenlabs.com](http://landenlabs.com/android/classtree/classtree.html)

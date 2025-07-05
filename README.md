# catandgrep
Here is my own implemantation of cat and grep for UNIX systems. In this readme.md you can find usage and guide for building project.
function of my utilities same as original cat and grep has. cat shows you text inside files and grep helps to find anything in file using regular expressions. 
## usage
folder ```build/bin/release``` contains executable files for cat and grep. you can execute it like ```./build/bin/release/grep ``` or just enter the folder and ``` ./grep ```.     
### cat
usage like original utility has 
```./cat [-flags] [filepath]```

you can also do it without flags or use text from stdin. you can also use several flags.

next you'll see explanation of every flag    
-E - shows end of lines with symbol $    
-b - numerates strings (only if string not empty)    
-n - numerates any strings    
-s - sqeezes blanks    
-t - shows tabs     
-v - shows all not printing symbols     
--help - shows help

### grep

here you can find something in your file using regular expressions. usage: 
```./grep [-flags] [expression] [filename]```    
you can use standard regular expression (i don't know if i may add here how to do it)
next all flags i implemented here:     

* -i - ignore case (upper or lower)    
* -c - counts matches    
* -v - inverts search (shows strings with no matches)    
* -l - shows files with matches     
* -n - shows line numbers     
* -w - word regex     
* -x - line regex    
* -r - recursive search
* -h - no filename
* -H - with filename
* -b - byte offset
* --help - shows help


also you can find inside the repository tests (./src/grep_test.sh and ./src/cat_test.sh)

## building
if you need to build this project use this inside the build folder:     
```cmake --build . --config release ```

i think that's all you need to know 

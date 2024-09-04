# Commands:

TIME in minutes (also later on min:sec)

leader start --> starts default sessions with 25min
leader start break (TIME) --> start 5 min break
leader start study (TIME) --> start 25-5-25
leader start study UNITS --> start UNITS * (25-5-25)
leader start PROJECTNAME --> create Project to log time into

leader set break TIME 
leader set study TIME

leader add PROJECTNAME
leader rm PROJECTNAME

leader list --> Show projects and the spend time inside of it

Project saving
    - PROJECTNAME TIME
    - Operations remove(), add()
    - differentiation between add time onto existing project 
    and adding a new project
    should be called add and update
    - inside save.c load(), save() Projectfile

Todo:
+ Refactor save.c

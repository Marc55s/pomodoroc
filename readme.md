# Commands

TIME = minutes (also later on min:sec)

- [x] leader start --> starts default sessions with 25min
- [x] leader start break (TIME) --> start 5 min break
- [x] leader start study (TIME) --> start 25-5-25
- [x] leader start PROJECTNAME --> create Project to log time into
---
- [ ] leader set break TIME 
- [ ] leader set study TIME
---
- [x] leader add PROJECTNAME
- [ ] leader rm PROJECTNAME

- [x] leader list --> Show projects and the spend time inside of it

## Project saving
- data saved inside project.txt
- PROJECTNAME TIME
- Operations remove(), update(), add()
- inside save.c load(), save() Projectfile

## Todo 
+ Refactor save.c
> Split up project operation and operations inside file  
> save.c should contain load() and save()  
> project.c should contain remove(), update(), add()

## Safety concerns/Bugs
- formatting while list projects
- Saving projects with the same name
- Saving/Overriding and listing is not saving everything


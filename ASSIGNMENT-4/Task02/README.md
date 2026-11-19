# Task 02 – From Requirement to Hierarchy

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task02_people.cpp` – virtual diamond hierarchy and construction demonstration.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task02_people.cpp -o task02
./task02
```
Windows PowerShell:
```powershell
g++ -std=c++17 -Wall -Wextra task02_people.cpp -o task02.exe
.\task02.exe
```

## Relationship summary
- `Student is-a Person`; `Staff is-a Person`.
- `TeachingAssistant is-a Student` and `is-a Staff` (multiple inheritance).
- `ResearchScholar is-a Student` and has-a fellowship value.
- `Address` would be has-a/member composition, not inheritance.
- Virtual inheritance ensures a `TeachingAssistant` has one shared `Person` base subobject (diamond problem solution).

## Access table for a member declared in Person
| Person member | public inheritance | protected inheritance | private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | inaccessible directly | inaccessible directly | inaccessible directly |

## Result
`Person` is constructed once for `TeachingAssistant` because both `Student` and `Staff` virtually inherit it. The most-derived class initializes the virtual base.

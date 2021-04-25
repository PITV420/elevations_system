# elevations_systeme
REPLACED STATIC ARRAYS WITH DYNAMIC MEMORY ALLOC

Task from recruiter
Requirements:
- up to 16 elevators
- calls for elevator - queue
- elevator's state:
	- busy or free
	- actual floor
	- destination (going up/down)
- simulation steps

Preconditions:
- init: all elevators on floor 0
- when going up: all floors above current floor can be handled by the elevator (cannot stop immediately - need one floor to slow down)
- when going down: all floors below current floor can be handled by the elevator (cannot stop immediately - need one floor to slow down)
- handling new calls: check state of all elevators (busy/free, actual floor, destination) and:
	- choose nearest elevator to the calling floor
	- when free, add new call to the elevator's queue
	- when busy, check direction in which it is moving:
		- if the same as new call (in respect of previous preconditions on which floors can elevator stop), add floor to it's queue and resort it in most ergonomically manner (closes floors are first to be handled)
		- if direction is different as new call, choose another elevator
		- if all elevators directions are different as new call, choose the one with shortest queue
- calls contains two informations: floor number and direction
- requests from within an elevator contains one information: destined floor
- when any of elevators reaches floor from queue, user will be asked for floor request (potentially could be in different direction as call's direction)

Simulation step:
- elevators are moving only one floor up/down when busy
- multiple calls can be requested

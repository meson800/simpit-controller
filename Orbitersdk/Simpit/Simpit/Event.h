//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_EVENT
#define SIMPIT_EVENT

#include <map>
class Event
{
public:
	Event() {id = 0; state = 0;}
	Event(int _id, int _state) { id = _id; state = _state;}
	int id, state;
};

inline bool operator==(const Event& lhs, const Event& rhs){return ((lhs.id == rhs.id) && (lhs.state == rhs.state)); }
inline bool operator!=(const Event& lhs, const Event& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Event& lhs, const Event& rhs)
{
	if (lhs.id < rhs.id)
		return true;
	if (lhs.id > rhs.id)
		return false;
	//now we have the case if id's are equal, check state
	if (lhs.state < rhs.state)
		return true;
	//return false then
	return false;
}
inline bool operator> (const Event& lhs, const Event& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Event& lhs, const Event& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Event& lhs, const Event& rhs){return !operator< (lhs,rhs);}



#endif
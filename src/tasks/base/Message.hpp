#pragma once

namespace tasks {

namespace base {

template<class T1, class T2> struct Message {
	using Token = T1;
	using Data = T2;

	Token token;
	Data data;
};

template<class T1> struct Event {
	using Token = T1;
	Token token;
};

}

}

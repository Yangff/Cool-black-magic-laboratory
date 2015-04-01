namespace fake {
	template<class T>
	class vector {
		char buf[_::ss[_::ToId<std::vector<T>::invoke]];
	};

	class string {
		char buf[_::ss[_::ToId<std::string>]];
		string(const char *){;};
		string(){;};
	};
};
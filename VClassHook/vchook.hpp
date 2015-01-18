#include <cstdio>
#pragma once
namespace Yangff {
	namespace BlackMagic {
		namespace VBT{
			template<class Target, class Magic, class MemberPtrA, class MemberPtrB> 
			struct _hooked {
				static void * oldAddr;
			};
			template <class Target, class Magic>
			class _vtbhook {
			private:
				Target *target;
				Magic *magic;
				void ** ovtbAddr, **nvtbAddr;
				int size;
				template<class MemberPtr>
				int GetOffset(MemberPtr ptr){
					int vid = *reinterpret_cast<int*>(reinterpret_cast<void*>(&ptr));
					vid--; vid /= (sizeof(void*));
					return vid;
				}
				template<class MemberPtr>
				void *getvFuncAddr(void *base, MemberPtr ptr) {
					int vid = GetOffset(ptr);
					void * vtb = ((void**)base)[0];
					void * _funcAddr = (((void **)vtb)[vid]);
					return _funcAddr;
				}
			public:
				_vtbhook(Target *target, Magic *magic):target(target), magic(magic){
					ovtbAddr = ((void***)target)[0];
					for (size = 0; ovtbAddr[size]; size++);
					nvtbAddr = new void*[size];
					for (int i = 0; i < size; i++)
						nvtbAddr[i] = ovtbAddr[i];
					((void***)target)[0] = nvtbAddr;
				}

				template<class MemberPtrA, class MemberPtrB>
				_vtbhook<Target, Magic> & hook(MemberPtrA ptrA, MemberPtrB ptrB){
					nvtbAddr[GetOffset(ptrA)] = getvFuncAddr(magic, ptrB);
					return *this;
				}
				
			}; // class
		}; // namespace 
	}; // namesapce 

}; // namespace 

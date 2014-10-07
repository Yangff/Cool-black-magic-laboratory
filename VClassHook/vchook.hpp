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
				template<class MemberPtr>
				void **getvFuncAddr(void *base, MemberPtr ptr) {
					int vid = *reinterpret_cast<int*>(reinterpret_cast<void*>(&ptr));
					vid--; vid /= (sizeof(void*));
					void * vtb = ((void**)base)[0];
					void ** _funcAddr = (((void **)vtb) + vid);
					return _funcAddr;
				}
			public:
				
				_vtbhook(Target *target, Magic *magic):target(target), magic(magic){;}

				template<class MemberPtrA, class MemberPtrB>
				_vtbhook<Target, Magic> & hook(MemberPtrA ptrA, MemberPtrB ptrB){
					if (_hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr == 0){
						void* oldAddr = *getvFuncAddr(target, ptrA);
						
						*getvFuncAddr(target, ptrA) = *getvFuncAddr(magic, ptrB);
						_hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr = oldAddr;
					}
					return *this;
				}
				template<class MemberPtrA, class MemberPtrB>
				_vtbhook<Target, Magic> & unhook(MemberPtrA ptrA, MemberPtrB ptrB){
					if (_hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr){
						void* oldAddr = _hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr;
						_hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr = 0;
						*getvFuncAddr(target, ptrA) = oldAddr;
					}
					return *this;
				}
			}; // class

			template<class Target, class Magic, class MemberPtrA, class MemberPtrB> 
				void* _hooked<Target, Magic, MemberPtrA, MemberPtrB>::oldAddr = 0;
		}; // namespace 
	}; // namesapce 

}; // namespace 

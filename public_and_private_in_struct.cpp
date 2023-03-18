#include "header_learning.h"

struct astruct
	{
		//public can also be used inside the struct, so can private
	public:
		int aint;
		void plusint(int & num)
		{
			num += 1;
			bint = num;
		}
		void print_bint()
		{
			std::cout << bint << std::endl;
		}
	private:
		int bint = 121;
	};

void public_and_private_in_struct()
{
	astruct struc;
	struc.aint = 666;
	//struc.bint = 222;CANNOT DO
	struc.print_bint();
	struc.plusint(struc.aint);
	std::cout << struc.aint << std::endl;
	struc.print_bint();
}
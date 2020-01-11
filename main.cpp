#include <iostream>
#include <algorithm>
#include <locale.h>
#include "Pentagon.h"
#include "queue.h"

void Menu1()
{
    std::cout << "1. Add figure in queue\n";
    std::cout << "2. Delete element of queue\n";
    std::cout << "3. Output element of queue\n";
    std::cout << "4. Output all elements of queue\n";
    std::cout << "5. Output the number of elements with area more then input\n";
    std::cout << "6. Add figure by index\n";
    std::cout << "0. Exit.\n";
}

void DeleteMenu()
{
    std::cout << "1. Delete the top element of queue\n";
    std::cout << "2. Delete figure by index\n";
}

void PrintMenu()
{
    std::cout << "1. Output the top element\n";
    std::cout << "2. Output the last element\n";
}

int main()
{
    Containers::Queue<Pentagon<int>> Myqueue;
	
	Pentagon<int> TempPentagon;

	while (true) {
		Menu1();
        int n, m;
		size_t ind;
		double s;
		std::cin >> n;
        switch (n)
        {
		case 1:
            TempPentagon.Read(std::cin);
            TempPentagon.Print(std::cout);
            Myqueue.push(TempPentagon);
			break;
		case 2:
            if (Myqueue.length() == 0)
            {
                std::cout << "Empty collection.\n";
                break;
            }
			DeleteMenu();
			std::cin >> m;
			switch (m) {
			case 1:
                Myqueue.pop();
				break;
			case 2:
                std::cout << "Input the index: ";
				std::cin >> ind;
                if (ind > Myqueue.length())
                {
                    std::cout << "Index is out of bourders.\n";
                    break;
                }
                Myqueue.delete_by_index(ind);
				break;
			default:
				break;
			}
			break;
		case 3:
            if (Myqueue.length() == 0)
            {
                std::cout << "Empty collection.\n";
                break;
            }
			PrintMenu();
			std::cin >> m;
			switch (m) {
			case 1:
                Myqueue.top().Print(std::cout);
				std::cout << std::endl;
				break;

			case 2:
                Myqueue.bottom().Print(std::cout);
				std::cout << std::endl;
				break;

			default:
                std::cout << "Incorrect input\n";
				break;
			}
			break;
		case 4:
            if (Myqueue.length() == 0)
            {
                std::cout << "Empty collection.\n";
                break;
            }
            std::for_each(Myqueue.begin(), Myqueue.end(), [](Pentagon<int>& X) { std::cout << "Element of queue:\n"; X.Print(std::cout); std::cout << std::endl; });
			break;
		case 5:
            std::cout << "Input the area:\n";
			std::cin >> s;
            std::cout << std::count_if(Myqueue.begin(), Myqueue.end(), [=](Pentagon<int>& X) {return X.Area() > s; }) << std::endl;
			break;
		case 6:
            std::cout << "Input the index\n";
			std::cin >> ind;
            std::cout << "Input coordinates of the pentagon\n";
			TempPentagon.Read(std::cin);
            Myqueue.insert_by_index(ind, TempPentagon);
			break;
        case 0:
            return 0;
		default:
            std::cout << "Incorrect input.\n";
		}
	}
	return 0;
}

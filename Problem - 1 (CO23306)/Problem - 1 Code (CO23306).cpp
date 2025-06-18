//Roll no :- CO23306, CSE
#include<iostream>
using namespace std;
void Add(int *A,int Lindex,int E)
{
	int i = 0;
	if (Lindex == 0)
	{
		A[Lindex] = E;  //Put element if array is empty
	}
	else //Operation if array is not empty
	{
		for(int i = 0; i < Lindex; i++)
		{
			if (E < A[i])
			{
				for (int j = Lindex; j > i; j--)
				{
					A[j] = A[j - 1];
				}
				A[i] = E;
				break;
			}
		}
		if (E >= A[Lindex -1])
		{
			A[Lindex] = E;
		}
	}
	cout << "Array after addition of element: ";
	for (int i = 0; i <= Lindex; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}
void Delete(int *A, int &Lindex, int E) 
{
    bool found = false;
    for (int i = 0; i < Lindex; i++) // Traverse the array to find the element E
	{ 
        if (A[i] == E) {
            found = true;
            for (int j = i; j < Lindex - 1; j++) // Shift elements to the left 
			{ 
                A[j] = A[j + 1];
            }
            Lindex--; // Decrease the last index as one element is deleted
            break;
        }
    }
    if (found) 
	{
        cout << "Element " << E << " deleted from the array." << endl;
        cout << "Array after deletion: ";
        for (int i = 0; i < Lindex; i++) 
		{
            cout << A[i] << " ";
        }
        cout << endl;
    } 
	else 
	{
        cout << "Element " << E << " not found in the array. Cannot delete." << endl;
    }
}
void InsertAtPosition(int *A, int &Lindex, int pos, int E)
{
    if (pos < 0 || pos > Lindex)
    {
        cout << "Invalid position!" << endl;
        return;
    }
    for (int i = Lindex; i > pos; i--) // Shift elements to the right 
    {
        A[i] = A[i - 1];
    }
    A[pos] = E; // Insert the new element at the specified position
    cout << "Array after insertion at position " << pos << ": ";
    for (int i = 0; i <= Lindex; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}
void Update(int *A, int Lindex, int index, int newValue) 
{
    if (index < 0 || index >= Lindex) 
	{
        cout << "Invalid index! Update failed." << endl;
        return;
    }
    A[index] = newValue;  // Update the element at the specified index
    cout << "Element at index " << index << " updated to " << newValue << "." << endl;
    cout << "Array after update: ";
    for (int i = 0; i < Lindex; i++) 
	{
        cout << A[i] << " ";
    }
    cout << endl;
}
int FindMax(int *A, int Lindex) 
{
    if (Lindex <= 0) 
	{
        cout << "Array is empty. No maximum value." << endl;
    }
    int maxVal = A[0];  // Initialize maxVal with the first element of the array
    for (int i = 1; i < Lindex; i++) 
	{
        if (A[i] > maxVal) 
		{
            maxVal = A[i];  // Update maxVal if current element is greater
        }
    }
    return maxVal;
}
int FindMin(int *A, int Lindex)
{
    if (Lindex <= 0) 
	{
        cout << "Array is empty. No minimum value." << endl;
    }
    int minVal = A[0];  // Initialize minVal with the first element of the array
    for (int i = 1; i < Lindex; i++) 
	{
        if (A[i] < minVal) 
		{
            minVal = A[i];  // Update minVal if current element is smaller
        }
    }
    return minVal;
}
int main()
{
	int A[10] = {1, 3, 5, 7, 9};
	int Lindex, E, pos, index, newValue, minVal, maxVal;
	cout<<"1. Add element"<<endl;
	cout<<"2. Insert an element in array"<<endl;
	cout<<"3. Delete element in array"<<endl;
	cout<<"4. Update element in array"<<endl;
	cout<<"5. Find Min Element of array"<<endl;
	cout<<"6. Find Max Element of array"<<endl;
	cout<<"Choice :- ";
	int choice;
	cin >> choice;
	switch(choice)
	{
		case 1:
			Lindex = 5;
	        E = 4;
	        Add(A, Lindex, E);
	        break;
	    case 2:
	    	Lindex = 5; 
            pos = 2;    
            E = 4;      
            InsertAtPosition(A, Lindex, pos, E);
            break;
        case 3:
        	Lindex = 5; 
            E = 5;       
            Delete(A, Lindex, E);
            break;
        case 4:
        	Lindex = 5;  
            index = 2;   
            newValue = 6; 
            Update(A, Lindex, index, newValue);
            break;
        case 5:
        	Lindex = 5;  
            minVal = FindMin(A, Lindex);
            cout << "Minimum value in the array: " << minVal << endl;
            break;
        case 6:
        	Lindex = 5;  // Current last index in array A 
            maxVal = FindMax(A, Lindex);
            cout << "Maximum value in the array: " << maxVal << endl;
            break;
        default:
        	cout << "Invalid choice" << endl;
        	return 0;
	}
	return 0;
}

#include <iostream>
#include <cstdio>
using namespace std;
float per_day(char Ex, float w)
{
    if (Ex == 'M') return 31 * w;
    if (Ex == 'F') return 27 * w;
}
float calculate_energy_from_food()
{
    int carbohydate;
    int fat, protein;
    cout << "Enter protein (g): ";
    cin >> protein;
    cout << "Enter carbohydate (g): ";
    cin >> carbohydate;
    cout << "Enter protein (g): ";
    cin >> fat;
    return 4 * (protein + carbohydate) + (9 * fat);
}
char input_Ex()
{
    char Ex;
    cout << "enter you ex [M or F]: ";
    cin >> Ex;
    while (Ex != 'M' && Ex != 'F')
    {
        cout << "Try Agian : ";
        cin >> Ex;
    }
    return Ex;
}
int main()
{
    int age;
    float weight;
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your weight: ";
    cin >> weight;

    char Ex = input_Ex();
    float Energy_per_day = per_day(Ex, weight);
    float all_energy = calculate_energy_from_food();
    float total = all_energy - Energy_per_day;

    if (total < 0)      cout << "Eat more than burn." << total * (-1) << " cal.";
    else if (total >0)  cout << "Eat more than burn." << total << " cal.";
    else                cout << "Eat equal to burn.";
}

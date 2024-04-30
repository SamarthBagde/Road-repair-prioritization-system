// int priority_pot()
// {
//     return -10;
// }

// int priority_road()
// {
//     return -7;
// }

// int priority_traffic()
// {
//     return -5;
// }

struct priorityValues
{
    int pot;
    int road;
    int traffic;
};

struct priorityValues getPriorityValues()
{
    struct priorityValues p;
    p.pot = -10;
    p.road = -7;
    p.traffic = -5;

    return p;
}
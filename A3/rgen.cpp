#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
namespace streamspace
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream output_str ;
        output_str << n ;
        return output_str.str() ;
    }
}
unsigned int random_street_generator ( unsigned int n )
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (n-2+1) +2;
    urandom.close();
    return (unsigned int) rand;
}
unsigned int random_line_generator (unsigned int n)
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (n-1+1) + 1;
    urandom.close();
    return (unsigned int) rand;
}
unsigned int random_wait (unsigned int n)
{
    std::ifstream urandom("/dev/urandom");

        if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int time = 3;
    urandom.read((char*)&time, sizeof(unsigned int));
    time = time % (n-5+1) + 5;
    urandom.close();
    return (unsigned int) time;
}

int random_coord_generator (unsigned int n)
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(int));
    rand = rand % (n+n);
    int out= rand - n ;
    urandom.close();
    return out;
}
void street_creation( vector<string> &street_struct , unsigned int street_no)
{
    string name = "street";
    for (unsigned int i=0; i < street_no; i++)
    {
        street_struct.push_back(name);
        name = name +'i';
    }
}
int maximum_of_coordinate_structs( int o1, int o2)
{
    int max_val;
    if ( o1 > o2)
    {
        max_val = o1;
        return max_val;
    }
    max_val = o2;
    return max_val;
}
int minimum_of_coordinate_structs( int o1, int o2)
{
    int min_val;
    if ( o1 > o2)
    {
        min_val = o2;
        return min_val;
    }

    min_val = o1;
    return min_val;
}
bool intersection_check( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double x_numerator, x_denominator, xcoor, y_numerator, y_denominator, ycoor;

    x_numerator = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    x_denominator = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    xcoor =  x_numerator / x_denominator;

    y_numerator = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    y_denominator = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    ycoor = y_numerator / y_denominator;

    int minimum_x1, minimum_x2, maximum_x1, maximum_x2, minimum_y1, minimum_y2, maximum_y1, maximum_y2;

    minimum_x1 = minimum_of_coordinate_structs(x1,x2);
    maximum_x1 = maximum_of_coordinate_structs(x1,x2);
    minimum_x2 = minimum_of_coordinate_structs(x3,x4);
    maximum_x2 = maximum_of_coordinate_structs(x3,x4);
    minimum_y1 = minimum_of_coordinate_structs(y1,y2);
    maximum_y1 = maximum_of_coordinate_structs(y1,y2);
    minimum_y2 = minimum_of_coordinate_structs(y3,y4);
    maximum_y2 = maximum_of_coordinate_structs(y3,y4);

    if ( minimum_x1<= xcoor &&  xcoor <= maximum_x1)
        if ( minimum_x2 <= xcoor && xcoor <= maximum_x2)
            if ( minimum_y1 <= ycoor && ycoor <= maximum_y1)
                if ( minimum_y2 <= ycoor && ycoor <= maximum_y2)
                    return true;
    return false;
}

bool point_addition ( vector<int> coordinate_struct, int x, int y)
{
    int s = coordinate_struct.size();
    if ( coordinate_struct.empty())
    {
        return true;
    }if ( s == 2)
    {
        if (( x == coordinate_struct[0]) && (y == coordinate_struct[1]) )
        {

            return false;
        }
        return true;
    }
    else
    {
           for (unsigned int i = 0; i < coordinate_struct.size(); i = i + 2){
            if (x == coordinate_struct[i] && y == coordinate_struct[i+1]){
                return false;
            }
        }

        double mod1, mod2;
        
        if ( x == coordinate_struct[s-2] && x == coordinate_struct[s-4])
            return false;

               if ( (x == coordinate_struct[s-2]) && (x != coordinate_struct[s-4]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=2; i = i-2 )
                {
                    if ( intersection_check(x,y,coordinate_struct[s-2],coordinate_struct[s-1],coordinate_struct[i-1],coordinate_struct[i],coordinate_struct[i-3],coordinate_struct[i-2]))
                        return false;

                }
                return true;
            }
        }

        if ( (coordinate_struct[s-4] == coordinate_struct[s-2]) && (x != coordinate_struct[s-2]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( intersection_check(x,y,coordinate_struct[s-2],coordinate_struct[s-1],coordinate_struct[i-1],coordinate_struct[i],coordinate_struct[i-3],coordinate_struct[i-2]))
                        return false;

                }

                return true;
            }
        }
        mod1 = ((y - coordinate_struct[s-1]) / (x-coordinate_struct[s-2]));
        mod2 = ((coordinate_struct[s-1]) - coordinate_struct[s-3]) / (coordinate_struct[s-2]-coordinate_struct[s-4]);

        if (mod1 == mod2)
            return false;

        else
        {

            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( intersection_check(x,y,coordinate_struct[s-2],coordinate_struct[s-1],coordinate_struct[i-1],coordinate_struct[i],coordinate_struct[i-3],coordinate_struct[i-2]))
                        return false;

                }

                return true;
            }

        }

    }

}
int main (int argc, char **argv)
 {
    std::string s_val, n_val, l_val, c_val;
    unsigned int default_s_val = 10, default_n_val = 5, default_l_val = 5, default_c_val = 20;
    int c;
    int street_no, l_num, x_cord, y_cord;
    unsigned int wait_seed;

    vector<string> street_struct; 
    vector<int> street_line_struct;
    vector<int> coordinate_struct;

    opterr = 0;
    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1) 
{
        switch (c) 
{
            case 's':
                s_val = optarg;
                default_s_val = std::atoi(s_val.c_str());
                if (default_s_val < 2)
                {
                    cerr << "Error: the s value should be greater than equal to 1"<<endl;
                    exit(1);
                }
                break;
            case 'n':
                n_val = optarg;
                default_n_val = std::atoi(n_val.c_str());
                if (default_n_val < 1)
                {
                    cerr << "Error: the n value should be atleast 1"<<endl;
                    exit(1);
                }
                break;
            case 'l':
                l_val = optarg;
                default_l_val = std::atoi(l_val.c_str());
                if (default_l_val < 5)
                {
                    cerr << "Error: the l value should atleast be 5"<<endl;
                    exit(1);
                }
                break;
            case 'c':
                c_val = optarg;
                default_c_val = std::atoi(c_val.c_str());
                if (default_c_val < 1)
                {
                    cerr << "Error: the c value cannot be less than 1"<<endl;
                    exit(1);
                }

                break;

            case '?':
                if (optopt == 's') 
               {
                    std::cerr << "Error: option -" << optopt
                              << " argument is required" << std::endl;
                    break;
                }
                else if (optopt == 'n') 
                {
                    std::cerr << "Error: option -" << optopt
                              << " argument is required" << std::endl;
                    break;
                }
                else if (optopt == 'l') 
                {
                    std::cerr << "Error: option -" << optopt
                              << " argument is required" << std::endl;
                    break;
                }
                else if (optopt == 'c') 
                {
                    std::cerr << "Error: option -" << optopt
                              << " argument is required" << std::endl;
                    break;
                }

                else
                    std::cerr << "Error: unknown option: " << optopt << std::endl;
                    break;
        }

    }

    while (true)
    {
        if ( !street_struct.empty())
        {
            for(std::vector<string>::iterator make = street_struct.begin(); make != street_struct.end(); make++)
            {
                cout<<"r "<<'"'<<*make<<'"'<<endl;

            }

            street_struct.clear();
          street_line_struct.clear();

        }
        street_no = random_street_generator(default_s_val);

        street_creation(street_struct, street_no);


        for (int j = 0; j < street_no; j++)
        {
            l_num = random_line_generator(default_n_val);
            street_line_struct.push_back(l_num);

        }

        int index = 0;

        for (unsigned int make1 = 0; make1 < street_line_struct.size(); make1++)
        {
            coordinate_struct.clear();    
            int times_count = 0;
            int error_count = 0;
            while ( times_count < street_line_struct[make1]+1 )
            {
                x_cord = random_coord_generator(default_c_val);
                y_cord = random_coord_generator(default_c_val);
                if (point_addition(coordinate_struct, x_cord, y_cord))
                {
                    coordinate_struct.push_back(x_cord);
                    coordinate_struct.push_back(y_cord);
                    times_count++;
                    error_count = 0;
                }

                else
                {

                    if ( error_count == 25)
                    {
                        cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                        exit(1);   
                    }

                    error_count++;
                }

            }

             string term_out;
            term_out = string("a \"") + street_struct[index] + "\" ";

            for (unsigned int mk = 0; mk < coordinate_struct.size(); mk = mk+2)
            {
                string a,b;
                if (coordinate_struct[mk]<0){
                  a = "-"+streamspace::to_string(coordinate_struct[mk]*(-1));
                } else {
                  a = streamspace::to_string(coordinate_struct[mk]);
                }
                if (coordinate_struct[mk+1]<0){
                  b = "-"+streamspace::to_string(coordinate_struct[mk+1]*(-1));
                } else {
                  b = streamspace::to_string(coordinate_struct[mk+1]);
                }
                term_out = term_out + '('+ a + ','+ b +')';
            }

            cout<<term_out<<endl;

            index++;
        }

            cout<<'g'<<endl;
            wait_seed = random_wait(default_l_val);
            usleep(wait_seed*1000000);

        }

return 0;
}











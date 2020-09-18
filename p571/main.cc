// #include <stopwatch.h>
// #include <eulerlib.h>
// #include <iostream>

// int main()
// {
//     Stopwatch timer("main");
    
//     size_t number = 109'746'121'381'517; // See A055085.
//     size_t count = 0, sum = 0;
//     std::string str;

//     while (true)
//     {
//         ++number;

//         str = euler::dec2baseN(number, 12);

//         if 
//         (
//             str.find("b") == std::string::npos ||
//             str.find("a") == std::string::npos ||
//             str.find("9") == std::string::npos ||
//             str.find("8") == std::string::npos ||
//             str.find("7") == std::string::npos ||
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 11);

//         if
//         (
//             str.find("a") == std::string::npos ||
//             str.find("9") == std::string::npos ||
//             str.find("8") == std::string::npos ||
//             str.find("7") == std::string::npos ||
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = std::to_string(number);

//         if 
//         (
//             str.find("9") == std::string::npos ||
//             str.find("8") == std::string::npos ||
//             str.find("7") == std::string::npos ||
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 9);

//         if 
//         (
//             str.find("8") == std::string::npos ||
//             str.find("7") == std::string::npos ||
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 8);

//         if 
//         (
//             str.find("7") == std::string::npos ||
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 7);

//         if 
//         (
//             str.find("6") == std::string::npos ||
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 6);

//         if 
//         (
//             str.find("5") == std::string::npos ||
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 5);

//         if 
//         (
//             str.find("4") == std::string::npos ||
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 4);
        
//         if 
//         (
//             str.find("3") == std::string::npos ||
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 3);
        
//         if 
//         (
//             str.find("2") == std::string::npos ||
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         str = euler::dec2baseN(number, 2);

//         if 
//         (
//             str.find("1") == std::string::npos ||
//             str.find("0") == std::string::npos
//         )
//             continue;

//         std::cout << "found " << count + 1 << "th number (" << number << ")\n";
//         sum += number;
//         ++count;

//         if (count == 10)
//             break;
//     }
    
//     std::cout << sum << '\n';

//     timer.time();
// }

// Code is bs and does not really work.

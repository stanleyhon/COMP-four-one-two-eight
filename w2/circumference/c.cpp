#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double doMath (double gradientA, double x1, double y1, double gradientB, double x2, double y2, double x3, double y3);

// gonna use goto hax to try all possible permutations of p1,p2,p3.
double ox1, oy1, ox2, oy2, ox3, oy3;
int hack = 0; // there are 6 possible permutations

int main (void) {
    double x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        hack = 0;
        ox1 = x1;
        oy1 = y1;
        ox2 = x2;
        oy2 = y2;
        ox3 = x3;
        oy3 = y3;
start_again:
#ifdef DEBUG
        cout << "\n\n\n";
#endif
        double gradientA, gradientB;
        double circumference = 0;
        if ((x2 - x1 != 0) && (x3 - x2 != 0)) {
            // p1 p2 forms a line
            gradientA = (y2 - y1) / (x2 - x1);
#ifdef DEBUG
            cout << "GradientA: " << gradientA << "\n";
#endif
            // p2 p3 forms a line
            gradientB = (y3 - y2) / (x3 - x2);
#ifdef DEBUG
            cout << "GradientB: " << gradientB << "\n";
#endif
            circumference = doMath (gradientA, x1, y1, gradientB, x2, y2, x3, y3);
        } else if ((x1 - x3 != 0) && (x3 - x2 != 0)) {
            gradientA = (y1 - y3) / (x1 - x3);

            gradientB = (y3 - y2) / (x3 - x2);
            circumference = doMath (gradientA, x1, y1, gradientB, x3, y3, x2, y2);
        } else if ((x2 - x3 != 0) && (x2 - x1 != 0)) {
            gradientA = (y2 - y3 / x2 - x3);
            
            gradientB = (y2 - y1 / x2 - x1);
            circumference = doMath (gradientA, x2, y2, gradientB, x1, y1, x3, y3);
        } else {
            // rearrange p1, p2, p3
            // 0 = p1 p2 p3
            // 1 = p1 p3 p2
            // 2 = p2 p1 p3
            // 3 = p2 p3 p1
            // 4 = p3 p1 p2
            // 5 = p3 p2 p1
            hack++;
            if (hack == 1) {
                x1 = ox1;
                y1 = oy1;
                x2 = ox3;
                y2 = oy3;
                x3 = ox2;
                y3 = oy2;
                goto start_again;
            } else if (hack == 2) {
                x1 = ox2;
                y1 = oy2;
                x2 = ox1;
                y2 = oy1;
                x3 = ox3;
                y3 = oy3;
                goto start_again;
            } else if (hack == 3) {
                x1 = ox2;
                y1 = oy2;
                x2 = ox3;
                y2 = oy3;
                x3 = ox1;
                y3 = oy1;
                goto start_again;
            } else if (hack == 4) {
                x1 = ox3;
                y1 = oy3;
                x2 = ox1;
                y2 = oy1;
                x3 = ox2;
                y3 = oy2;
                goto start_again;
            } else if (hack == 5) {
                x1 = ox3;
                y1 = oy3;
                x2 = ox2;
                y2 = oy2;
                x3 = ox1;
                y3 = oy1;
                goto start_again;
            } else {
                cout << "SOMETHING WENT WRONG\n";
            }
        }

        printf ("%.2f\n", circumference);
    }
    return 0;
}

double doMath (double gradientA, double x1, double y1, double gradientB, double x2, double y2, double x3, double y3) {
#ifdef DEBUG
    cout << "GradientA: " << gradientA << "\n";
    cout << "GradientB: " << gradientB << "\n";
#endif
    // intersections of the perpendiculars at midpoint gives 
    // center.
    // solve the two equasions for x you get
    double centerX = ((gradientA * gradientB) * (y1 - y3))
                     +
                     (gradientB * (x1 + x2))
                     -
                     (gradientA * (x2 + x3));
    centerX = centerX / (2 * (gradientB - gradientA));
#ifdef DEBUG
    cout << "CenterX: " << centerX << "\n";
#endif

    // We now have the x coordinate.
    
    // Sub it into one of the perpendiculars from before:
    double centerY;
    if (gradientA != 0) {
        centerY = (-1 / gradientA) * (centerX - ((x1 + x2)/2)) + ((y1 + y2) / 2);
    } else {
        centerY = (-1 / gradientB) * (centerX - ((x2 + x3)/2)) + ((y2 + y3) / 2);
    }
#ifdef DEBUG
    cout << "CenterY: " << centerY << "\n";
#endif

    // distance from center to any point gives radius
    double radius = sqrt (((centerY - y1) * (centerY - y1)) + ((centerX - x1) * (centerX - x1)));
#ifdef DEBUG
    cout << "Radius: " << radius << "\n";
#endif
    return (radius * 2 * 3.141592653589793);
}

            /*
           // find the pair where the x don't match
           if ((x1 != x2) && (y1 != y2)) {
#ifdef DEBUG
            cout << "CASE1\n";
#endif
               gradientA = (y1 - y2) / (x1 - x2);
               if (x1 - x3 != 0) {
                   gradientB = (y1 - y3) / (x1 - x3);
                   circumference = doMath (gradientA, x1, y1, gradientB, x2, y2, x3, y3);
               } else {
                   gradientB = (y2 - y3) / (x2 - x3);
                   circumference = doMath (gradientA, x2, y2, gradientB, x1, y1, x3, y3);
               }
           } else if ((x1 != x3) && (y1 != y3)) {
               gradientA = (y1 - y3) / (x1 - x3);
               if (x1 - x2 != 0) {
#ifdef DEBUG
            cout << "CASE2a\n";
#endif
                   gradientB = (y1 - y2) / (x1 - x2);
                   circumference = doMath (gradientA, x1, y1, gradientB, x3, y3, x2, y2);
               } else {
#ifdef DEBUG
            cout << "CASE2b\n";
#endif
                   gradientB = (y3 - y2) / (x3 - x2);
                   circumference = doMath (gradientA, x3, y3, gradientB, x1, y1, x2, y2);
               }
           } else {
#ifdef DEBUG
            cout << "CASE3\n";
#endif
               gradientA = (y1 - y2) / (x1 - x2);
               if (x1 - x3 != 0) {
                   gradientB = (y1 - y3) / (x1 - x3);
                   circumference = doMath (gradientA, x1, y1, gradientB, x2, y2, x3, y3);
               } else {
                   gradientB = (y2 - y3) / (x2 - x3);
                   circumference = doMath (gradientA, x2, y2, gradientB, x1, y1, x3, y3);
               }
           }*/

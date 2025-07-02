#include <iostream>
#include <cmath>

// Base constants
const double A0 = 3.7;
const double B0 = 2.1;
const double C0 = 5.4;
const double D0 = 1.8;

// Function 1: Difference of squares identity
// Uses: (a+b)(a-b) = a² - b²
double S1(double k) {
    double A = 2*k + A0;
    double B = k + B0;
    double C = -k + C0;
    double D = 3*k + D0;
    
    // Create expressions that will cancel
    double term1 = (A + B) * (A - B);  // = A² - B²
    double term2 = A * A - B * B;      // = A² - B²
    
    double term3 = (C + D) * (C - D);  // = C² - D²
    double term4 = C * C - D * D;      // = C² - D²
    
    // term1 - term2 = 0, term3 - term4 = 0
    double S = (term1 - term2) + (term3 - term4) + 3*k + 2;
    
    return S;
}

// Function 2: Trigonometric identity
// Uses: sin²(x) + cos²(x) = 1
double S2(double k) {
    double A = k + A0;
    double B = 2*k + B0;
    double C = -k + C0;
    double D = k/2 + D0;
    
    double x = 0.5;  // Any constant angle
    
    // These will sum to A, B, C, D respectively
    double termA = A * sin(x) * sin(x) + A * cos(x) * cos(x);  // = A * 1 = A
    double termB = B * sin(x) * sin(x) + B * cos(x) * cos(x);  // = B * 1 = B
    double termC = C * sin(x) * sin(x) + C * cos(x) * cos(x);  // = C * 1 = C
    double termD = D * sin(x) * sin(x) + D * cos(x) * cos(x);  // = D * 1 = D
    
    // Now subtract the expanded forms
    double S = termA + termB - termC - termD
             - (k + A0) - (2*k + B0) + (-k + C0) + (k/2 + D0)
             + 5*k + 7;
    
    return S;
}

// Function 3: Logarithmic cancellation
// Uses: ln(e^x) = x and e^(ln(x)) = x
double S3(double k) {
    double A = 3*k + A0 + 10;  // Ensure positive
    double B = k + B0 + 10;
    double C = 2*k + C0 + 10;
    double D = k/3 + D0 + 10;
    
    // These operations cancel
    double term1 = log(exp(log(A)));  // = log(A)
    double term2 = exp(log(log(A)));  // = log(A)
    
    double term3 = log(A * B / C / D);  // = log(A) + log(B) - log(C) - log(D)
    double term4 = log(A) + log(B) - log(C) - log(D);  // Same as term3
    
    double S = (term1 - term2) + (term3 - term4) + 2*k + 1;
    
    return S;
}

// Function 4: Algebraic expansion
// Uses: (a+b+c+d)² = a² + b² + c² + d² + 2(ab + ac + ad + bc + bd + cd)
double S4(double k) {
    double A = k + A0;
    double B = -2*k + B0;
    double C = 3*k + C0;
    double D = -k/2 + D0;
    
    double sum = A + B + C + D;
    double sumSquared = sum * sum;
    
    double individualSquares = A*A + B*B + C*C + D*D;
    double crossTerms = 2*(A*B + A*C + A*D + B*C + B*D + C*D);
    
    // sumSquared = individualSquares + crossTerms, so their difference is 0
    double S = sumSquared - individualSquares - crossTerms + 4*k - 3;
    
    return S;
}

// Function 5: Fraction addition identity
// Uses: a/b + c/d = (ad + bc)/(bd)
double S5(double k) {
    double A = 2*k + A0 + 1;
    double B = k + B0 + 1;
    double C = -k + C0 + 1;
    double D = 3*k + D0 + 1;
    
    // Two ways to compute the same thing
    double frac1 = A/B + C/D;
    double frac2 = (A*D + B*C)/(B*D);
    
    // Additional cancelling terms
    double term1 = (A*C + B*D)/(A + B);
    double term2 = (A*C + B*D)/(A + B);
    
    double S = (frac1 - frac2) + (term1 - term2) + 6*k + 10;
    
    return S;
}

// Function 6: Product expansion
// Uses: (a+b)(c+d) = ac + ad + bc + bd
double S6(double k) {
    double A = k/2 + A0;
    double B = 2*k + B0;
    double C = -k + C0;
    double D = k + D0;
    
    double product1 = (A + B) * (C + D);
    double product2 = A*C + A*D + B*C + B*D;
    
    // These are equal, so difference is 0
    double S = product1 - product2 + 7*k/2 - 8;
    
    return S;
}

// Function 7: Complex nested expression
double S7(double k) {
    double A = 2*k + A0;
    double B = -k + B0;
    double C = 3*k + C0;
    double D = k/2 + D0;
    
    // Create a complex expression that simplifies
    double num = (A*B + C*D)*(A + C) - A*A*B - C*C*D;
    double den = B + D;
    
    // This equals A*C
    double frac = num / den;
    
    // So frac - A*C = 0
    double S = frac - A*C + 8*k + 12;
    
    return S;
}

// Function 8: Square root identity
// Uses: (√a + √b)² = a + b + 2√(ab)
double S8(double k) {
    double offset = 20;  // Ensure all values are positive
    double A = 2*k + A0 + offset;
    double B = k + B0 + offset;
    double C = k/2 + C0 + offset;
    double D = 3*k + D0 + offset;
    
    double sqrtSum1 = sqrt(A) + sqrt(B);
    double expanded1 = A + B + 2*sqrt(A*B);
    
    double sqrtSum2 = sqrt(C) + sqrt(D);
    double expanded2 = C + D + 2*sqrt(C*D);
    
    // sqrtSum² - expanded = 0 for both
    double S = sqrtSum1*sqrtSum1 - expanded1 + sqrtSum2*sqrtSum2 - expanded2 + 9*k/2 + 15;
    
    return S;
}

// Function 9: Exponential/logarithm combination
double S9(double k) {
    double A = k + A0 + 5;
    double B = 2*k + B0 + 5;
    double C = -k/2 + C0 + 5;
    double D = 3*k + D0 + 5;
    
    // exp(ln(x)) = x
    double term1 = exp(log(A*B)) - A*B;  // = 0
    double term2 = exp(log(C*D)) - C*D;  // = 0
    
    // ln(x^n) = n*ln(x)
    double term3 = log(pow(A, 3)) - 3*log(A);  // = 0
    double term4 = log(pow(B, 2)) - 2*log(B);  // = 0
    
    double S = term1 + term2 + term3 + term4 + 11*k/2 + 20;
    
    return S;
}

// Function 10: Matrix determinant property
double S10(double k) {
    double A = 3*k + A0;
    double B = -k + B0;
    double C = 2*k + C0;
    double D = k/4 + D0;
    
    // For 2x2 matrix [[a,b],[c,d]], det = ad - bc
    // det([[A,B],[C,D]]) = AD - BC
    
    double det1 = A*D - B*C;
    
    // Also can compute as: det = (A+B)*(C+D) - AC - BD - 2BC
    double det2 = (A+B)*(C+D) - A*C - B*D - 2*B*C;
    
    // det1 = det2, so their difference is 0
    double S = det1 - det2 + 10*k - 25;
    
    return S;
}

int main() {
    std::cout << "Testing hidden linear functions:\n";
    std::cout << "Format: S(k) = result [expected linear function]\n\n";
    
    // Test for a few k values
    double k_values[] = {0, 1, 2, 5, 10, -2, -5};
    
    std::cout << "Function results:\n";
    for (int i = 1; i <= 10; i++) {
        std::cout << "\nS" << i << "(k):\n";
        bool isLinear = true;
        double slope = 0, intercept = 0;
        
        // Calculate slope using two points
        double k1 = 1.0, k2 = 2.0;
        double s1, s2;
        
        switch(i) {
            case 1: s1 = S1(k1); s2 = S1(k2); break;
            case 2: s1 = S2(k1); s2 = S2(k2); break;
            case 3: s1 = S3(k1); s2 = S3(k2); break;
            case 4: s1 = S4(k1); s2 = S4(k2); break;
            case 5: s1 = S5(k1); s2 = S5(k2); break;
            case 6: s1 = S6(k1); s2 = S6(k2); break;
            case 7: s1 = S7(k1); s2 = S7(k2); break;
            case 8: s1 = S8(k1); s2 = S8(k2); break;
            case 9: s1 = S9(k1); s2 = S9(k2); break;
            case 10: s1 = S10(k1); s2 = S10(k2); break;
        }
        
        slope = (s2 - s1) / (k2 - k1);
        intercept = s1 - slope * k1;
        
        // Test all k values
        for (double k : k_values) {
            double result;
            switch(i) {
                case 1: result = S1(k); break;
                case 2: result = S2(k); break;
                case 3: result = S3(k); break;
                case 4: result = S4(k); break;
                case 5: result = S5(k); break;
                case 6: result = S6(k); break;
                case 7: result = S7(k); break;
                case 8: result = S8(k); break;
                case 9: result = S9(k); break;
                case 10: result = S10(k); break;
            }
            
            double expected = slope * k + intercept;
            std::cout << "  k=" << k << ": " << result;
            
            if (std::abs(result - expected) < 0.0001) {
                std::cout << " ✓";
            } else {
                std::cout << " ✗ (expected " << expected << ")";
                isLinear = false;
            }
            std::cout << "\n";
        }
        
        if (isLinear) {
            std::cout << "  Linear function: S(k) = " << slope << "*k + " << intercept << "\n";
        }
    }
    
    std::cout << "\n=== Summary of Linear Functions ===\n";
    for (int i = 1; i <= 10; i++) {
        double k1 = 1.0, k2 = 2.0;
        double s1, s2;
        
        switch(i) {
            case 1: s1 = S1(k1); s2 = S1(k2); break;
            case 2: s1 = S2(k1); s2 = S2(k2); break;
            case 3: s1 = S3(k1); s2 = S3(k2); break;
            case 4: s1 = S4(k1); s2 = S4(k2); break;
            case 5: s1 = S5(k1); s2 = S5(k2); break;
            case 6: s1 = S6(k1); s2 = S6(k2); break;
            case 7: s1 = S7(k1); s2 = S7(k2); break;
            case 8: s1 = S8(k1); s2 = S8(k2); break;
            case 9: s1 = S9(k1); s2 = S9(k2); break;
            case 10: s1 = S10(k1); s2 = S10(k2); break;
        }
        
        double slope = (s2 - s1) / (k2 - k1);
        double intercept = s1 - slope * k1;
        
        std::cout << "S" << i << "(k) = " << slope << "*k + " << intercept << "\n";
    }
    
    return 0;
}
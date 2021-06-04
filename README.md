# Calculator
Uni project of building a calculator with function, variable and imaginary numbers support

## Usage
Launch with */i* and */o* parameters

* /i [input file path]
* /o [output file path]

This calculator supports variables. To add a variable use following syntax:
[var name] = [expression]

Variable expressions may include other variables.

Expressions without names and equal signs are considred to be root and their solutions are written into an output file.

**NOTE: use 'j' as imagianry unit. In output imaginary unit is represented as 'i', as usual**

**NOTE: use 'PI' and 'e' for corresponding constants**

Input example:
```
exp(-j*PI*alpha*len/v0)
alpha = sqrt(PI*len/(s1+s2))
s1 = cos(real(S11)*real(S22))
s2 = (sin(imag(S11*S22)))^2
len = 191.76
v0 = 299.799
S11 = -0.01-0.92j
S22 = 0.0001+0.997j

(abc + xxx*2)/(z^3*(asd- 50))
abc = 5.34
xxx = -97.12
z = 23.23
asd = -2.5

e^(PI*j)

1-1j-1+j

5+-1

imag(5+10j)

phase(j)
phase(10)
phase(-j)
phase(-100)

log(16,2)
```

Corresponding output:
```
alpha = (sqrt(PI*len/(s1+s2)))
s1 = (cos(real(S11)*real(S22)))
s2 = ((sin(imag(S11*S22)))^2)
len = (191.76)
v0 = (299.799)
S11 = (-0.01-0.92j)
S22 = (0.0001+0.997j)
abc = (5.34)
xxx = (-97.12)
z = (23.23)
asd = (-2.5)

Solving roots: 

exp(-j*PI*alpha*len/v0) = 0.588164 + 0.808742i
(abc+xxx*2)/(z^3*(asd-50)) = 0.000287 + -0.000000i
e^(PI*j) = -1.000000 + 0.000000i
1-1j-1+j = 0.000000 + 0.000000i
5+-1 = 4.000000 + 0.000000i
imag(5+10j) = 0.000000 + 10.000000i
phase(j) = 1.570796 + 0.000000i
phase(10) = 0.000000 + 0.000000i
phase(-j) = 4.712389 + 0.000000i
phase(-100) = 0.000000 + 0.000000i
log(16,2) = 4.000000 + 0.000000i
```
### Warning
This calculator has no syntax checker. If bad syntax is encountered, unexpected errors might occur.

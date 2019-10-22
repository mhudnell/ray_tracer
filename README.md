A simple ray tracer C++11 implementation built following Peter Shirley's tutorial series: [Ray Tracing in One Weekend](https://github.com/RayTracing/raytracing.github.io)

## Compiling
release:
```bash
g++ -std=c++11 test_ppm_out.cpp -o test_ppm_out.exe
```

debug:
```bash
g++ -ggdb -std=c++11 test_ppm_out.cpp -o test_ppm_out.exe
```

## Running
```bash
test_ppm_out.exe > test_ppm_out.ppm
```

## Debugging
```bash
gdb test_ppm_out.exe
```

Add a breakpoint
```bash
(gdb) b file:line_number
```

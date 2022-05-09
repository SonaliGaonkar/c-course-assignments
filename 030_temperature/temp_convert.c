#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float Fahrenheit_conversion(float INPUT, char *argv[])
{
    if (strcmp(argv[1], "k") == 0 || strcmp(argv[1], "K") == 0 || strcmp(argv[1], "kelvin") == 0 || strcmp(argv[1], "Kelvin") == 0)
    {
        return 9 / 5 * (INPUT - 273.15) + 32;
    }
    else if (strcmp(argv[1], "°C") == 0 || strcmp(argv[1], "c") == 0 || strcmp(argv[1], "C") == 0 || strcmp(argv[1], "celsius") == 0 || strcmp(argv[1], "Celsius") == 0)
    {
        return (9 / 5 * INPUT) + 32;
    }
    else
    {
        fprintf(stderr, "temp_convert: error: Unrecognized  INPUT scale %s", argv[1]);
        abort();
        return EXIT_FAILURE;
    }
}

float Kelvin_conversion(float INPUT, char *argv[])
{
    if (strcmp(argv[1], "°F") == 0 || strcmp(argv[1], "f") == 0 || strcmp(argv[1], "F") == 0 || strcmp(argv[1], "fahrenheit") == 0 || strcmp(argv[1], "Fahrenheit") == 0)
    {
        return 5 / 9 * (INPUT - 32) + 273.15;
    }
    else if (strcmp(argv[1], "°C") == 0 || strcmp(argv[1], "c") == 0 || strcmp(argv[1], "C") == 0 || strcmp(argv[1], "celsius") == 0 || strcmp(argv[1], "Celsius") == 0)
    {
        return INPUT + 273.15;
    }
    else
    {
        fprintf(stderr, "temp_convert: error: Unrecognized  INPUT scale %s", argv[1]);
        abort();
        return EXIT_FAILURE;
    }
}

float Celsius_conversion(float INPUT, char *argv[])
{
    if (strcmp(argv[1], "°F") == 0 || strcmp(argv[1], "f") == 0 || strcmp(argv[1], "F") == 0 || strcmp(argv[1], "fahrenheit") == 0 || strcmp(argv[1], "Fahrenheit") == 0)
    {
        return (INPUT - 32) * (5 / 9);
    }
    else if (strcmp(argv[1], "k") == 0 || strcmp(argv[1], "K") == 0 || strcmp(argv[1], "kelvin") == 0 || strcmp(argv[1], "Kelvin") == 0)
    {
        return INPUT - 273.15;
    }
    else
    {
        fprintf(stderr, "temp_convert: error: Unrecognized  INPUT scale %s", argv[1]);
        abort();
        return EXIT_FAILURE;
    }
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "temp_convert: error: Not enough arguments.\n");
        fprintf(stderr, "Usage: temp_convert INPUT_SCALE OUTPUT_SCALE [ TEMPERATURE]...");
        abort();
        return EXIT_FAILURE;
    }
    for (int arg = 3; arg < argc; arg++)
    {
        if (strcmp(argv[2], "°F") == 0 || strcmp(argv[2], "f") == 0 || strcmp(argv[2], "F") == 0 || strcmp(argv[2], "fahrenheit") == 0 || strcmp(argv[2], "Fahrenheit") == 0)
        {
            float output = Fahrenheit_conversion(atof(argv[arg]), argv);
            printf("%.2f\n", output);
        }
        else if (strcmp(argv[2], "k") == 0 || strcmp(argv[2], "K") == 0 || strcmp(argv[2], "kelvin") == 0 || strcmp(argv[2], "Kelvin") == 0)
        {
            float output = Kelvin_conversion(atof(argv[arg]), argv);
            printf("%f\n", output);
        }
        else if (strcmp(argv[2], "°C") == 0 || strcmp(argv[2], "c") == 0 || strcmp(argv[2], "C") == 0 || strcmp(argv[2], "celsius") == 0 || strcmp(argv[2], "Celsius") == 0)
        {
            float output = Celsius_conversion(atof(argv[arg]), argv);
            printf("%.2f\n", output);
        }
        else
        {
            fprintf(stderr, "temp_convert: error: Unrecognized  INPUT scale %s", argv[2]);
            abort();
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

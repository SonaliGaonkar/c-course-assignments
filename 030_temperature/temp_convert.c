#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isInList(const char *str, const char *strings[])
{
    for (; *strings != NULL; strings++)
        if (strcmp(str, *strings) == 0)
            return true;
    return false;
}

bool celsiusIsScale(const char *str)
{
    const char *celsiusStrings[] = {"C", "°C", "c", "Celsius", "celsius", NULL};
    return isInList(str, celsiusStrings);
}

double celsiusToKelvin(double celsius)
{
    return celsius + 273.15;
}

double celsiusFromKelvin(double kelvin)
{
    return kelvin - 273.15;
}

bool fahrenheitIsScale(const char *str)
{
    const char *fahrenheitStrings[] = {"F", "°F", "f", "Fahrenheit", "fahrenheit", NULL};
    return isInList(str, fahrenheitStrings);
}

double fahrenheitToKelvin(double fahrenheit)
{
    return (fahrenheit + 459.67) * 5 / 9;
}

double fahrenheitFromKelvin(double kelvin)
{
    return kelvin * 9 / 5 - 459.67;
}

bool kelvinIsScale(const char *str)
{
    const char *kelvinStrings[] = {"K", "k", "Kelvin", "kelvin", NULL};
    return isInList(str, kelvinStrings);
}

double kelvinToKelvin(double kelvin)
{
    return kelvin;
}

double kelvinFromKelvin(double kelvin)
{
    return kelvin;
}
struct TemperatureScale
{
    bool (*isScale)(const char *str);
    double (*toKelvin)(double);
    double (*fromKelvin)(double);
};

struct TemperatureScale celsius = {
    celsiusIsScale,
    celsiusToKelvin,
    celsiusFromKelvin,
};

struct TemperatureScale fahrenheit = {
    fahrenheitIsScale,
    fahrenheitToKelvin,
    fahrenheitFromKelvin,
};

struct TemperatureScale kelvin = {
    kelvinIsScale,
    kelvinToKelvin,
    kelvinFromKelvin,
};

typedef double (*converter_t)(double);
converter_t getToKelvinFunction(char *temperatureScale)
{
    struct TemperatureScale temperatureScales[] = {
        celsius, fahrenheit, kelvin};
    for (int i = 0; i < sizeof(temperatureScales) / sizeof(temperatureScales[0]); i++)
    {
        if (temperatureScales[i].isScale(temperatureScale))
        {
            return temperatureScales[i].toKelvin;
        }
    }
    fprintf(stderr, "error: Unsupported temperature scale: %s\n", temperatureScale);
    exit(EXIT_FAILURE);
}

converter_t getFromKelvinFunction(char *temperatureScale)
{
    struct TemperatureScale temperatureScales[] = {
        celsius, fahrenheit, kelvin};
    for (int i = 0; i < sizeof(temperatureScales) / sizeof(temperatureScales[0]); i++)
    {
        if (temperatureScales[i].isScale(temperatureScale))
        {
            return temperatureScales[i].fromKelvin;
        }
    }
    fprintf(stderr, "error: Unsupported temperature scale: %s\n", temperatureScale);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "%s: error: Not enough arguments.\nUsage: %s INPUT_SCALE OUTPUT_SCALE [TEMPERATURE]...\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    converter_t toKelvin = getToKelvinFunction(argv[1]);
    converter_t fromKelvin = getFromKelvinFunction(argv[2]);

    for (int i = 3; i < argc; i++)
    {
        double inputTemperature = atof(argv[i]);
        double temperature = toKelvin(inputTemperature);
        double outputTemperature = fromKelvin(temperature);

        printf("%f\n", outputTemperature);
    }
    return EXIT_SUCCESS;
}

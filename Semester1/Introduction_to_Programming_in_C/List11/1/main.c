// 0 - success
// 1 - critical problem
// 2 - warning
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "fgetline.h"
#include <math.h>
#define PI 3.14159265359

struct rgb {
    int red;
    int green;
    int blue;
};

int width, height;

struct rgb get_color(char *color)
{
    if (!strcmp(color, "black")) return (struct rgb){0, 0, 0};
    if (!strcmp(color, "red")) return (struct rgb){255, 0, 0};
    if (!strcmp(color, "green")) return (struct rgb){0, 255, 0};
    if (!strcmp(color, "blue")) return (struct rgb){0, 0, 255};
    if (!strcmp(color, "yellow")) return (struct rgb){255, 255, 0};
    return (struct rgb){255, 255, 255};
}

void set_pixel(int x, int y, struct rgb c, struct rgb img[height][width])
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    img[y][x] = c;
}

double to_radians(double angle)
{
    return angle * (PI / 180.0);
}

void draw_ellipse(char *color, int x_mid, int y_mid, int x_len, int y_len, int angle, struct rgb img[height][width])
{
    double ang = to_radians(angle);
    struct rgb c = get_color(color);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double d_x = x - x_mid;
            double d_y = y - y_mid;
            // Rotate the point
            double new_x = d_x * cos(ang) + d_y * sin(ang);
            double new_y = -d_x * sin(ang) + d_y * cos(ang);
            // Check if the point belongs to the ellipse 
            double a_square = (double)x_len * x_len;
            double b_square = (double)y_len * y_len;
            double res = new_x * (new_x / a_square);
            res += new_y * (new_y / b_square);
            if (res <= 1) set_pixel(x, y, c, img);
        }
    }
}

void draw_rectangle(char *color, int x_mid, int y_mid, int x_len, int y_len, int angle, struct rgb img[height][width])
{
    double ang = to_radians(angle);
    struct rgb c = get_color(color);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double d_x = x - x_mid;
            double d_y = y - y_mid;
            // Rotate the point
            double new_x = d_x * cos(ang) + d_y * sin(ang);
            double new_y = -d_x * sin(ang) + d_y * cos(ang);
            // Check if the point belongs to the rectangle
            if (new_x >= -x_len / 2 && new_x <= x_len / 2 && new_y >= -y_len / 2 && new_y <= y_len / 2)
                set_pixel(x, y, c, img);
        }
    }
}

void draw_polygon(char *color, int n_vertices, int vertices[n_vertices][2], struct rgb img[height][width])
{
    struct rgb c = get_color(color);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            bool ok = true;
            for (int i = 0; i < n_vertices; i++)
            {
                int x1 = vertices[i][0];
                int y1 = vertices[i][1];
                int x2 = vertices[(i + 1) % n_vertices][0];
                int y2 = vertices[(i + 1) % n_vertices][1];
                int res = (y - y1) * (x2 - x1) - (y2 - y1) * (x - x1);
                // Verify if the point is on the correct side of all polygon edges
                if (res < 0)
                {
                    ok = false;
                    break;
                }
            }
            if (ok) set_pixel(x, y, c, img);
        }
    }
}

int main(int argc, char **argv)
{
    bool binary = false;
    char *filename = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--binary") || !strcmp(argv[i], "-b")) binary = true;
        else if (filename == NULL) filename = argv[i];
        else
        {
            fprintf(stderr, "Invalid arguments!\n");
            return 1;
        }
    }

    if (scanf(" %d %d", &width, &height) != 2)
    {
        fprintf(stderr, "Width and height must be integers!\n");
        return 1;
    }
    if (width <= 0 || height <= 0)
    {
        fprintf(stderr, "Width and height must be integers greater than zero!\n");
        return 1;
    }
    getchar();
    char figure[20], color[20];
    struct rgb img[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) img[i][j] = (struct rgb){255, 255, 255};
    int line_cnt = 0;
    bool problem = false;
    while (1)
    {
        char *line = fgetline(stdin, NULL);
        line_cnt++;
        if (line == NULL) break;
        if (*line == '\n') 
        {
            free(line);
            continue;
        }
        char *ptr = line;
        int idx = 0;
        if (*ptr == ' ')
        {
            while (*ptr == ' ') ptr++;
        }
        while (*ptr != ' ' && *ptr != '\n') 
        {
            figure[idx] = *ptr;
            idx++;
            ptr++;
        }
        figure[idx] = '\0';
        idx = 0;
        if (*ptr == '\0')
        {
            fprintf(stderr, "Not enough arguments in line %d!\n", line_cnt);
            problem = 1;
            free(line);
            continue;
        }
        ptr++;
        while (*ptr != ' ' && *ptr != '\n')
        {
            color[idx] = *ptr;
            idx++;
            ptr++;
        }
        color[idx] = '\0';
        if (*ptr == '\0')
        {
            fprintf(stderr, "Not enough arguments in line %d!\n", line_cnt);
            problem = 1;
            free(line);
            continue;
        }
        ptr++;
        if (!strcmp("ellipse", figure))
        {
            int x_mid, y_mid, x_len, y_len, angle;
            int count;
            int args = sscanf(ptr, "%d %d %d %d %d%n", &x_mid, &y_mid, &x_len, &y_len, &angle, &count);
            if (x_len <= 0 || y_len <= 0)
            {
                fprintf(stderr, "Lengths must be greater than zero in line %d!\n", line_cnt);
                problem = 1;
                free(line);
                continue;
            }
            if (args != 5) 
            {
                fprintf(stderr, "Not enough arguments in line %d!\n", line_cnt);
                problem = 1;
                free(line);
                continue;
            }
            ptr += count;
            if (*ptr != '\n') 
            {
                fprintf(stderr, "Too many arguments in line %d!\n", line_cnt);
                problem = 1;
            }
            draw_ellipse(color, x_mid, y_mid, x_len, y_len, angle, img);
        }
        else if (!strcmp("rectangle", figure))
        {
            int x_mid, y_mid, x_len, y_len, angle;
            int count;
            int args = sscanf(ptr, "%d %d %d %d %d%n", &x_mid, &y_mid, &x_len, &y_len, &angle, &count);
            if (x_len <= 0 || y_len <= 0)
            {
                fprintf(stderr, "Lengths must be greater than zero in line %d!\n", line_cnt);
                problem = 1;
                free(line);
                continue;
            }
            if (args != 5) 
            {
                fprintf(stderr, "Not enough arguments in line %d!\n", line_cnt);
                problem = 1;
                free(line);
                continue;
            }
            ptr += count;
            if (*ptr != '\n') 
            {
                fprintf(stderr, "Too many arguments in line %d!\n", line_cnt);
                problem = 1;
            }
            draw_rectangle(color, x_mid, y_mid, x_len, y_len, angle, img);
        }
        else if (!strcmp("polygon", figure))
        {
            int vertices[100][2];
            int n_vertices = 0;
            while (*ptr != '\n')
            {
                int x, y, count;
                int args = sscanf(ptr, "%d %d%n", &x, &y, &count);
                if (args != 2) break;
                vertices[n_vertices][0] = x;
                vertices[n_vertices][1] = y;
                n_vertices++;
                ptr += count;
                while (*ptr == ' ') ptr++;
            }
            if (n_vertices < 3)
            {
                fprintf(stderr, "Not enough vertices for a polygon in line %d!\n", line_cnt);
                problem = 1;
                free(line);
                continue;
            }
            if (*ptr != '\n') 
            {
                fprintf(stderr, "Too many arguments in line %d!\n", line_cnt);
                problem = 1;
            }
            draw_polygon(color, n_vertices, vertices, img);
        }
        else
        {
            fprintf(stderr, "Unknown figure in line %d!\n", line_cnt);
            problem = 1;
        }
        free(line);
    }

    FILE *f = NULL;
    if (filename) 
    {
        if (binary) f = fopen(filename, "wb");
        else f = fopen(filename, "w");
        if (!f) 
        {
            fprintf(stderr, "Cannot open the file\n");
            problem = 1;
            f = NULL;
        }
    }
    if (binary)
    {
        if (filename) fprintf(f, "P6\n%d %d\n255\n", width, height);
        else printf("P6\n%d %d\n255\n", width, height);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                struct rgb curr = img[i][j];
                if (filename)
                {
                    fputc(curr.red, f);
                    fputc(curr.green, f);
                    fputc(curr.blue, f);
                }
                else 
                {
                    putchar(curr.red);
                    putchar(curr.green);
                    putchar(curr.blue);
                }
            }
        }
        return 0;
    }
    else
    {
        if (filename) fprintf(f, "P3\n%d %d\n255\n", width, height);
        else printf("P3\n%d %d\n255\n", width, height);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                struct rgb curr = img[i][j];
                if (filename) fprintf(f, "%d %d %d\n", curr.red, curr.green, curr.blue);
                else printf("%d %d %d\n", curr.red, curr.green, curr.blue);
            }
        }
    }
    if (filename && fclose(f)) 
    {
        fprintf(stderr, "Cannot close the file!\n");
        problem = 1;
    }
    if (problem) return 2;
    return 0;
}
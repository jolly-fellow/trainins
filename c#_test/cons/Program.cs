using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;


public struct Light {
    public int distance, duration;
}

class Solution
{

    static bool is_red(int speed, int dist, int dur) {
        return (18 * dist) % (10 * speed * dur) >= (5 * speed * dur);
    }

    static void Main(string[] args)
    {

        int speed = int.Parse(Console.ReadLine()); // km/h
        int light_count = int.Parse(Console.ReadLine()); 

        Light[] lights = new Light[light_count];

        for (int i = 0; i < light_count; ++i)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            lights[i].distance = int.Parse(inputs[0]); // meters
            lights[i].duration = int.Parse(inputs[1]); // seconds
        }


        for(int i = 0; i < light_count; i++)
        {
            if (is_red(speed, lights[i].distance, lights[i].duration))
            {
                --speed;
                i = -1;
            }                
        }

        Console.WriteLine(speed);
    }

    // To debug: Console.Error.WriteLine("Debug messages...");
}
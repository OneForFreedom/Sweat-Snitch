---
title: Sweat-Snitch
author: OneForFreedom
description: Measure both your temps and himidity!
journal created: 11/11/25
project created: Idk
---

# Entry 1, Getting started. 

Since this is retrospective. I don't have images on Demand. So ig I'll have to explain what I did and how it looked like.

Okay, so first I fired up KiCad. I made the project and started following the tutorial. I knew what I wanted to make so I started to create it. 

I Decided to use the Sensirion SHT20-TR-1.5KS. A nifty but cheap sensor. But WAYYY to expensive to pcba. A stupid mistake I made.

Here's an image of it: 
![C53865_C53865-ÕýÃæ](https://github.com/user-attachments/assets/0ccde46f-29cc-48d3-abc9-709d5cb5c8ef)


I also went with 2 resistors and one screen. I made it sort of look like a rectangle at that point. Although I have 0 pull ups. So it wasn't gonna work

On top of that, I also made the scematics and pcb and downloaded it and uploaded it to jlc. But then, quite obvously. the damn thing was too expensive!

So I hard to restart.

At that point I was getting fustrated after putting 5 hours into it all. Including the coding which was just me giving prompts to ai and then semi modifying it.

Time taken 5 Hours.

# Entry 2, Start over. 

So I decided to restart from scratch. I used a cheaper, Economic type sensor Called the TI HDC1080DMBR 

Here's an image of that:
![C82227_C82227-ÕýÃæ](https://github.com/user-attachments/assets/5dbfea81-b3fc-4df3-b62e-7ff033f14df1)

I added a somewhat correct system to have pull ups.

I also added another oled, added an i2c expander. and then redid the code. 

This took me around 8-10 hours (I'll say 9), Mainly cuz 

1. I suck at Hardware rn, and I'm still in that sort of kindergarden stage and
2. I don't do alot of hardware as in elecricity, I'm more of a simple cad guy, although I do plan on one day using a server fan to use for a makeshift solder fume extractor. But for the meanwhile, Looks like im breathing it in.
3. I had to learn ALOT of things on about this. Like libraries and i2c expanders.

Time taken 9 Hours.

# Entry 3, ONE. FINAL. ENTRY.

- Okay, so I researched prices and made a proper bom. 
- I completed the readme
- I double checked every component then uploaded it onto github.
- I also added the arduino. Coded properly - I hope.

This is one hefty project. Give or take a few mins I spent around 1 hour doing all this.

Time taken 1 hour

Total time taken 15 Hours.

I'll continue journalling the making process!

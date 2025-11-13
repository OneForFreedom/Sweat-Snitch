# Sweat-Snitch

Humidifier and Temp reader and projector, Top oled shows temp whilst bottom oled shows humidity. It also has a i2c multiplex because both oleds use the same lib.


A border of one px will show if temps are over 30 degrees C and a border of 4px will show if temps are over 40 degrees C


And no. This won't work if  you completely submerge it in water.

## Project Images

 ![3D Front View](/Images/3D%20F.png)
 ![3D Back View](/Images/3D%20B.png)
 ![Schematic](/Images/Schematic.png)
 ![PCB](/Images/PCB.png)

 ## BOM (Bill Of Materials)

| Item                | Quantity | Unit Price (USD) | Total Price (USD) | Link                        |
| ------------------- | -------- | ---------------- | ----------------- | --------------------------- |
| PCB                 | 1        | 37.76            | 37.76             | [link](https://jlcpcb.com) |
| 120x64 OLED         | 1        | 8.36             | 8.36              | [link](https://www.aliexpress.com/item/1005009059402520.html?spm=a2g0o.cart.0.0.54c038da04MvbX&mp=1&pdp_npi=5%40dis%21USD%21USD%209.20%21USD%208.36%21%21USD%208.36%21%21%21%4021038da617629913850046188e4225%2112000047762448537%21ct%21UK%216063356903%21%211%210) |
| 32x128 OLED         | 1        | 6.95             | 6.95              | [link](https://www.aliexpress.com/item/1005008918700196.html?spm=a2g0o.cart.0.0.54c038da04MvbX&mp=1&pdp_npi=5%40dis%21USD%21USD%208.17%21USD%206.95%21%21USD%206.81%21%21%21%4021038da617629913850046188e4225%2112000047202792620%21ct%21UK%216063356903%21%211%210) |
| TCA9548A            | 1        | 3.87             | 3.87              | [link](https://www.aliexpress.com/item/1005007045955724.html?spm=a2g0o.productlist.main.33.76691rzg1rzg7r&algo_pvid=0d004523-b776-46f6-858b-fdce07ac84ff&algo_exp_id=0d004523-b776-46f6-858b-fdce07ac84ff-30&pdp_ext_f=%7B%22order%22%3A%227%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21GBP%211.07%210.97%21%21%211.36%211.23%21%40211b615317629902107267153ea55b%2112000039209725776%21sea%21UK%216063356903%21X%211%210%21n_tag%3A-29919%3Bd%3A3fd4c7f7%3Bm03_new_user%3A-29895&curPageLogUid=Wrrspp4YM6PT&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007045955724%7C_p_origin_prod%3A) |
| Seeed Studio RP2040 | 1        | 8.74            | 8.74             | [link](https://thepihut.com/products/seeed-xiao-rp2040?variant=53975380263297) |
| **Total**           |          |                  | **65.68**         |                             |

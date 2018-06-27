
#include <phys253.h>
#include <LiquidCrystal.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit: and with 11110111
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit: or with 00001000
#endif

const uint8_t ir_pin = 4;
int sin_vals[] = {0, 1, 3, 4, 6, 7, 9, 10, 12, 14, 15, 17, 18, 20, 21, 23, 25, 26, 28, 29, 31, 32, 34, 36, 37, 39, 40, 42, 43, 45, 47, 48, 50, 51, 53, 54, 56, 58, 59, 61, 62, 64, 65, 67, 69, 70, 72, 73, 75, 76, 78, 80, 81, 83, 84, 86, 87, 89, 90, 92, 94, 95, 97, 98, 100, 101, 103, 105, 106, 108, 109, 111, 112, 114, 115, 117, 119, 120, 122, 123, 125, 126, 128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 144, 145, 147, 148, 150, 151, 153, 154, 156, 158, 159, 161, 162, 164, 165, 167, 168, 170, 171, 173, 175, 176, 178, 179, 181, 182, 184, 185, 187, 188, 190, 192, 193, 195, 196, 198, 199, 201, 202, 204, 205, 207, 209, 210, 212, 213, 215, 216, 218, 219, 221, 222, 224, 225, 227, 228, 230, 232, 233, 235, 236, 238, 239, 241, 242, 244, 245, 247, 248, 250, 251, 253, 254, 256, 257, 259, 260, 262, 264, 265, 267, 268, 270, 271, 273, 274, 276, 277, 279, 280, 282, 283, 285, 286, 288, 289, 291, 292, 294, 295, 297, 298, 300, 301, 303, 304, 306, 307, 309, 310, 312, 313, 315, 316, 318, 319, 321, 322, 324, 325, 327, 328, 330, 331, 333, 334, 336, 337, 339, 340, 342, 343, 344, 346, 347, 349, 350, 352, 353, 355, 356, 358, 359, 361, 362, 364, 365, 367, 368, 369, 371, 372, 374, 375, 377, 378, 380, 381, 383, 384, 386, 387, 388, 390, 391, 393, 394, 396, 397, 399, 400, 402, 403, 404, 406, 407, 409, 410, 412, 413, 414, 416, 417, 419, 420, 422, 423, 424, 426, 427, 429, 430, 432, 433, 434, 436, 437, 439, 440, 442, 443, 444, 446, 447, 449, 450, 451, 453, 454, 456, 457, 458, 460, 461, 463, 464, 466, 467, 468, 470, 471, 472, 474, 475, 477, 478, 479, 481, 482, 484, 485, 486, 488, 489, 491, 492, 493, 495, 496, 497, 499, 500, 501, 503, 504, 506, 507, 508, 510, 511, 512, 514, 515, 516, 518, 519, 521, 522, 523, 525, 526, 527, 529, 530, 531, 533, 534, 535, 537, 538, 539, 541, 542, 543, 545, 546, 547, 549, 550, 551, 553, 554, 555, 557, 558, 559, 561, 562, 563, 564, 566, 567, 568, 570, 571, 572, 574, 575, 576, 578, 579, 580, 581, 583, 584, 585, 587, 588, 589, 590, 592, 593, 594, 596, 597, 598, 599, 601, 602, 603, 604, 606, 607, 608, 609, 611, 612, 613, 615, 616, 617, 618, 620, 621, 622, 623, 625, 626, 627, 628, 629, 631, 632, 633, 634, 636, 637, 638, 639, 641, 642, 643, 644, 645, 647, 648, 649, 650, 652, 653, 654, 655, 656, 658, 659, 660, 661, 662, 664, 665, 666, 667, 668, 670, 671, 672, 673, 674, 675, 677, 678, 679, 680, 681, 683, 684, 685, 686, 687, 688, 690, 691, 692, 693, 694, 695, 696, 698, 699, 700, 701, 702, 703, 704, 706, 707, 708, 709, 710, 711, 712, 714, 715, 716, 717, 718, 719, 720, 721, 722, 724, 725, 726, 727, 728, 729, 730, 731, 732, 734, 735, 736, 737, 738, 739, 740, 741, 742, 743, 744, 745, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 765, 766, 767, 768, 769, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 801, 802, 803, 804, 805, 806, 807, 808, 809, 810, 811, 812, 813, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 828, 829, 830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 839, 840, 841, 842, 843, 844, 845, 846, 847, 847, 848, 849, 850, 851, 852, 853, 854, 854, 855, 856, 857, 858, 859, 860, 860, 861, 862, 863, 864, 865, 865, 866, 867, 868, 869, 870, 870, 871, 872, 873, 874, 875, 875, 876, 877, 878, 879, 879, 880, 881, 882, 883, 883, 884, 885, 886, 887, 887, 888, 889, 890, 890, 891, 892, 893, 894, 894, 895, 896, 897, 897, 898, 899, 900, 900, 901, 902, 903, 903, 904, 905, 906, 906, 907, 908, 908, 909, 910, 911, 911, 912, 913, 913, 914, 915, 916, 916, 917, 918, 918, 919, 920, 920, 921, 922, 922, 923, 924, 925, 925, 926, 927, 927, 928, 929, 929, 930, 930, 931, 932, 932, 933, 934, 934, 935, 936, 936, 937, 938, 938, 939, 939, 940, 941, 941, 942, 943, 943, 944, 944, 945, 946, 946, 947, 947, 948, 949, 949, 950, 950, 951, 951, 952, 953, 953, 954, 954, 955, 955, 956, 957, 957, 958, 958, 959, 959, 960, 960, 961, 962, 962, 963, 963, 964, 964, 965, 965, 966, 966, 967, 967, 968, 968, 969, 969, 970, 970, 971, 971, 972, 972, 973, 973, 974, 974, 975, 975, 976, 976, 977, 977, 978, 978, 978, 979, 979, 980, 980, 981, 981, 982, 982, 983, 983, 983, 984, 984, 985, 985, 986, 986, 986, 987, 987, 988, 988, 988, 989, 989, 990, 990, 990, 991, 991, 992, 992, 992, 993, 993, 994, 994, 994, 995, 995, 995, 996, 996, 997, 997, 997, 998, 998, 998, 999, 999, 999, 1000, 1000, 1000, 1001, 1001, 1001, 1002, 1002, 1002, 1003, 1003, 1003, 1004, 1004, 1004, 1004, 1005, 1005, 1005, 1006, 1006, 1006, 1006, 1007, 1007, 1007, 1008, 1008, 1008, 1008, 1009, 1009, 1009, 1009, 1010, 1010, 1010, 1010, 1011, 1011, 1011, 1011, 1012, 1012, 1012, 1012, 1013, 1013, 1013, 1013, 1014, 1014, 1014, 1014, 1014, 1015, 1015, 1015, 1015, 1015, 1016, 1016, 1016, 1016, 1016, 1017, 1017, 1017, 1017, 1017, 1017, 1018, 1018, 1018, 1018, 1018, 1018, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
int skipped = 0;

const uint8_t prescale = 4;

void setup() {
    
    #include<phys253setup.txt>
    Serial.begin(9600);
    // Set prescaler to 16 - see 
    // http://yaab-arduino.blogspot.com/2015/02/fast-sampling-from-analog-input.html
    if(prescale&4) {
        sbi(ADCSRA, ADPS2);
    } else {
        cbi(ADCSRA, ADPS2);
    }

    if(prescale&2) {
        sbi(ADCSRA, ADPS1);
    } else {
        cbi(ADCSRA, ADPS1);
    }

    if(prescale&1) {
        sbi(ADCSRA, ADPS0);
    } else {
        cbi(ADCSRA, ADPS0);
    }
}

long sin_t(int x) {
    // x is in 1/4096th's of a full revolution
    int section = (x>>10)&(3);
    int mod = x&1023;
    if(section == 0) {
        return sin_vals[mod];
    } else if(section == 1) {
        return sin_vals[1023-mod];
    } else if(section == 2) {
        return -sin_vals[mod];
    }
    return -sin_vals[1023-mod];
}

long cos_t(int x) {
    x += 4095;
    int section = (x>>10)&(3);
    int mod = x&1023;
    if(section == 0) {
        return sin_vals[1023-mod];
    } else if(section == 1) {
        return -sin_vals[mod];
    } else if(section == 2) {
        return -sin_vals[1023-mod];
    }
    return sin_vals[mod];
}

long lo_amt = 0, hi_amt = 0, min_read, max_read;

long ins[10];

int had;

long diff_cnt = 0;
// in 
long freq_amt(long samplePeriod, long goalPeriod) {
    uint8_t analog_reference = 1;
    min_read = 1023;
    max_read = 0;
    skipped = 0;
    lo_amt = 0;
    diff_cnt = 0;
    hi_amt = 0;
    int bck = 0;
    float sample_rate = 16000.0/13/(1<<prescale); // kHz, need to update this because of extra cycles between beginning and ending..
    float lo_freq = 1;
    float hi_freq = 10;
    int lo_ang_delta = int(lo_freq/sample_rate*4096); // in revolutions
    int hi_ang_delta = int(hi_freq/sample_rate*4096); // in revolutions
    had = lo_ang_delta;
    long lo_cos = 0;
    long hi_cos = 0;
    long lo_sin = 0;
    long hi_sin = 0;
    long lo_ang = 0;
    long hi_ang = 0;
    ADMUX = (analog_reference << 6) | ir_pin;
    sbi(ADCSRA, ADSC);
    int s_count = 400;
    long avg = 0;
    for(int it=0;it<s_count;++it) {
        while(bit_is_set(ADCSRA, ADSC)) ++skipped;
        int lo_byte = ADCL;
        int hi_byte = ADCH;
        avg += (hi_byte<<8) | lo_byte;

        ADMUX = (analog_reference << 6) | ir_pin;
        sbi(ADCSRA, ADSC);
    }
    avg /= s_count;
    int s_count_ten = s_count/10;
    for(int it=0;it<s_count;++it) {
        while(bit_is_set(ADCSRA, ADSC)) ++skipped;
        int lo_byte = ADCL;
        int hi_byte = ADCH;
        long tval = (hi_byte<<8) | lo_byte;
        tval -= avg;

        ADMUX = (analog_reference << 6) | ir_pin;
        sbi(ADCSRA, ADSC);

        min_read = min(tval, min_read);
        max_read = max(tval, max_read);

        lo_amt = tval;
        hi_amt = tval;

        lo_cos += tval*cos_t(lo_ang);
        lo_sin += tval*sin_t(lo_ang);
        if(tval*cos_t(lo_ang) < 0) {
            ++diff_cnt;
        }
        //if(s_count_ten > it) {
            hi_cos += tval*cos_t(hi_ang);
            hi_sin += tval*sin_t(hi_ang);
        //}

        lo_ang += lo_ang_delta;
        hi_ang += hi_ang_delta;
        lo_ang &= 4095;
        hi_ang &= 4095;
    }

    float lo_amt_f = sqrt((float) lo_cos*lo_cos + (float) lo_sin*lo_sin);
    float hi_amt_f = sqrt((float) hi_cos*hi_cos + (float) hi_sin*hi_sin);
    lo_amt = lo_amt_f;
    hi_amt = hi_amt_f;
    //lo_amt = lo_cos;// + lo_sin;
    //hi_amt = hi_cos;// + hi_sin;
}

int my_analog_read(int ir_pin)
{
    uint8_t analog_reference = 1;
    ADMUX = (analog_reference << 6) | ir_pin;
    sbi(ADCSRA, ADSC);

        for(int i=0;i<1000;++i);
  
        while(bit_is_set(ADCSRA, ADSC));
        int lo_byte = ADCL;
        int hi_byte = ADCH;
        long tval = (hi_byte<<8) | lo_byte;

        return tval;
}


void loop() {

    int val = my_analog_read(ir_pin);

    unsigned long start = micros();
    long lo_tot = 0;
    long hi_tot = 0;
    int sample_cnt = 10;
    for(int i=0;i<sample_cnt;++i) {
        freq_amt(0,0);
        lo_tot += lo_amt/sample_cnt;
        hi_tot += hi_amt/sample_cnt;
    }
    unsigned long fin = micros();

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(lo_tot);
    LCD.setCursor(12, 0);
    LCD.print(diff_cnt);
    LCD.setCursor(0, 1);
    LCD.print(hi_tot);
    delay(300);
    /*
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(fin-start);
    LCD.setCursor(0, 1);
    LCD.print(had);
    delay(1300);
    /*
    LCD.clear();
    delay(50);
    LCD.setCursor(0,0);
    LCD.print(fin-start);
    delay(300);
    LCD.clear();
    delay(50);
    LCD.setCursor(0,0);
    LCD.print(min_read);
    LCD.print(", ");
    LCD.print(max_read);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    delay(300);
    LCD.setCursor(0, 0);
    LCD.print(lo_amt);
    LCD.setCursor(0, 1);
    LCD.print(hi_amt);
    
    /*
    LCD.setCursor(0,0);
    for(int i=0;i<5;++i) {
      LCD.print(ins[i]);
      LCD.print(",");
    }
    LCD.setCursor(0,1);
    for(int i=3;i<10;++i) {
      LCD.print(ins[i]);
      LCD.print(",");
    }
    */
    //delay(1000); 
    /*
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(sin_t(512));
    LCD.print(",");
    LCD.print(sin_t(1024));
    LCD.setCursor(0, 1);
    LCD.print(cos_t(512));
    LCD.print(",");
    LCD.print(cos_t(1024));
    delay(1000); */
    LCD.clear();
    delay(100);
}


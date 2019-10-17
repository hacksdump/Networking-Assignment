#!/usr/bin/python3
import csv

SENDER = "10.61.68.21"
with open('../part_1/capture.csv') as csvfile:
    capture = csv.DictReader(csvfile)
    count = 0
    total_packet_size = 0
    incoming_packet_count = 0
    outgoing_packet_count = 0
    send_times = []
    receive_times = []
    for row in capture:
        count += 1
        total_packet_size += int(row["Length"])
        time = 0
        try:
            time = float(row["Time"])
        except:
            pass
        if row["Source"] == SENDER:
            outgoing_packet_count += 1
            send_times.append(time)
        else:
            incoming_packet_count += 1
            receive_times.append(time)
    
    total_send_interval = 0
    for i in range(len(send_times) - 1):
        total_send_interval += send_times[i+1] - send_times[i]
    avg_send_interval = total_send_interval / (len(send_times) - 1)
    

    average_packet_size = total_packet_size / count
    print("Average packet size:", average_packet_size)
    print("Average ratio of incoming to outgoing packets:", incoming_packet_count/outgoing_packet_count)
    print("Average time interval between packets sent:", avg_send_interval)
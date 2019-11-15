#!./env/bin/python
# coding: utf-8

import pandas as pd

shark = pd.read_csv('../part_1/capture.csv')

IP = '10.61.68.21'

print("Average Packet Size: {} bytes".format(sum(shark['Length'])/len(shark['Length'])))

print('Average no of Packets sent per flow: {}'.format(shark[shark['Source']==IP].groupby(['Source','Destination'])['Length'].count().mean()))

print('Average no of Bytes sent per flow: {}'.format(shark[shark['Source']==IP].groupby(['Source','Destination'])['Length'].sum().mean()))

x = len(shark[shark['Destination']==IP]['Length'])/len(shark[shark['Source']==IP]['Length'])
print('Average Ratio of incoming to outgoing packets: {}'.format(x))

x = (shark[shark['Source']==IP]['Time'])
ans = (x.iloc[len(x)-1] - x.iloc[0])/len(x)
print('Average Time interval between packets sent: {}'.format(ans))

x = (shark[shark['Destination']==IP]['Time'])
ans = (x.iloc[len(x)-1] - x.iloc[0])/len(x)
print('Average Time interval between packets received: {}'.format(ans))

n_destinations = len(set(shark[shark['Source']==IP]['Destination']))
print('Average ratio of connections to number of destination IPs: {}'.format(len(shark)/n_destinations))

avg_duration = (shark.groupby(['Source','Destination'])['Time'].max() - shark.groupby(['Source','Destination'])['Time'].min()).mean()
print('Average flow duration: {}'.format(avg_duration))

print('Average no of Packets received per flow: {}'.format(shark[shark['Destination']==IP].groupby(['Source','Destination'])['Length'].count().mean()))

print('Average no of Bytes received per flow: {}'.format(shark[shark['Destination']==IP].groupby(['Source','Destination'])['Length'].sum().mean()))

ans = sum(shark[shark['Destination']==IP]['Length'])/sum(shark[shark['Source']==IP]['Length'])
print('Average ratio of incoming to outgoing bytes: {}'.format(ans))


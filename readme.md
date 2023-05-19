# Irrigation system

![](./images/block_diagram.png)


## Storage Configuration 

This is the memry map used to store:
- Blynk Token
- Telegram
  - Token
  - Chat ID

To manage the storage the EEPROM ligrary is used

The memorymap is as follow, each column represents a byte:


<table>
    <thead>
        <tr>
            <th>0</th>
            <th>1</th>
            <th>2</th>
            <th>3</th>
            <th>4</th>
            <th>5</th>
            <th>6</th>
            <th>7</th>
            <th>8</th>
            <th>9</th>
            <th>10</th>
            <th>11</th>
            <th>12</th>
            <th>13</th>
            <th>14</th>
            <th>15</th>
            <th>16</th>
            <th>17</th>
            <th>18</th>
            <th>19</th>
        </tr>
    </thead>
    <tbody>
      <tr>
        <td colspan=10>ChatID</td>
        <td colspan=10>Telegram Token</td>
       </tr>
       <tr>
         <td colspan=20>Telegram Token</td>
       </tr>
       <tr>
         <td colspan=18>Telegram token</td>
         <td colspan=2>Blynk token</td>
       </tr>
       <tr>
         <td colspan=20>Blynk token</td>
       </tr>
       <tr>
         <td colspan=18>Blynk token</td>
         <td colspan=2>padding</td>
       </tr>
       <tr>
         <td colspan=1>Flag</td>
         <td colspan=3>Unused</td>
         <td colspan=8>Configuration relay1</td>
         <td colspan=8>Configuration relay2</td>
       </tr>
       <tr>
         <td colspan=8>Configuration relay3</td>
         <td colspan=8>Configuration relay4</td>
       </tr>
   </tbody>
</table>

where the the time configuration per each relay is shown in the table below, the time span is a 4 bytes number the least significan byte is stored on the first byte.

<table>
    <thead>
        <tr>
            <th>0</th>
            <th>1</th>
            <th>2</th>
            <th>3</th>
            <th>4</th>
            <th>5</th>
            <th>6</th>
            <th>7</th>
        </tr>
    </thead>
    <tbody>
      <tr>
        <td colspan=1>Hour</td>
        <td colspan=1>Min</td>
        <td colspan=1>Seg</td>
        <td colspan=1>time span (lsb)</td>
        <td colspan=1>time span</td>
         <td colspan=1>time span</td>
         <td colspan=1>time span (msb)</td>
         <td colspan=1>Days</td>
       </tr>
   </tbody>
</table>

One byte is used to represent all the days, where one bit corresponds to a day as describbed in the table below

<table>
    <thead>
        <tr>
            <th colspan=8>Byte</tr>
        </tr>
        <tr>
            <th>7</th>
            <th>6</th>
            <th>5</th>
            <th>4</th>
            <th>3</th>
            <th>2</th>
            <th>1</th>
            <th>0</th>
        </tr>
    </thead>
    <tbody>
      <tr>
        <td>n/a</td>
        <td>Saturaday</td>
        <td>Friday</td>
        <td>Thursday</td>
        <td>Wednesday</td>
        <td>Tuesday</td>
        <td>Monday</td>
        <td>Sunday</td>
      </tr>
   </tbody>
</table>


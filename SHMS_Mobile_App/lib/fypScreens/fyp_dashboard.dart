import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:semacs_app/NewDashboard.dart';
import 'package:semacs_app/firebase service.dart';
import 'package:semacs_app/fypScreens/documents%20page.dart';
import 'package:syncfusion_flutter_charts/charts.dart';
import 'package:syncfusion_flutter_charts/sparkcharts.dart';
import 'package:syncfusion_flutter_gauges/gauges.dart';
import 'package:url_launcher/url_launcher.dart';

class FYPDashboard extends StatefulWidget {
  const FYPDashboard({super.key});

  @override
  State<FYPDashboard> createState() => _FYPDashboardState();
}

class _FYPDashboardState extends State<FYPDashboard> {
  late DatabaseReference _dbref;
  late String lastUpdateHour = '--';
  late String lastUpdateMin = '--';
  late String lastUpdateDay = '--';
  late String lastUpdateMonth = '--';
  late String lastUpdateYear = '--';

  var patientChart;


  late List<num> heartRateList = [];
  late List<num> bloodOxygenList = [];
  late List<num> bodyTemperatureList = [];

  @override
  void initState() {
    super.initState();
    _dbref = FirebaseDatabase.instance.ref();
    readData();
    _dbref.onValue.listen((event) {
      setState(() {
        lastUpdateHour = DateTime.now().hour.toString();
        lastUpdateMin = DateTime.now().minute.toString();
        lastUpdateDay = DateTime.now().day.toString();
        lastUpdateMonth = DateTime.now().month.toString();
        lastUpdateYear = DateTime.now().year.toString();
      });
    });

    DatabaseReference heartRateObj = FirebaseDatabase.instance.ref('sensor/HeartBeat');
    heartRateObj.onValue.listen(
          (DatabaseEvent event) {
            setState(() {
              heartRate = event.snapshot.value;
              heartRateList.add(heartRate);
              print(heartRateList);
            });
      },
    );

    DatabaseReference bloodOxygenObj = FirebaseDatabase.instance.ref('sensor/SpO2');
    bloodOxygenObj.onValue.listen(
          (DatabaseEvent event) {
            setState(() {
              bloodOxygen = event.snapshot.value;
              bloodOxygenList.add(bloodOxygen);
              print(bloodOxygenList);
            });
      },
    );

    DatabaseReference bodyTemperatureObj =
    FirebaseDatabase.instance.ref('Body Parameters/Body Temperature');
    bodyTemperatureObj.onValue.listen(
          (DatabaseEvent event) {
            setState(() {
              bodyTemperature = event.snapshot.value;
              bodyTemperatureList.add(bodyTemperature);
              print(bodyTemperatureList);
            });
      },
    );

  }

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.white,
        toolbarHeight: 80.h,
        leadingWidth: 250.w,
        leading: Padding(
          padding: EdgeInsets.only(left: 20.w, top: 0.w),
          child: Container(
            child: Row(
              children: [
                CircleAvatar(
                  maxRadius: 20.w,
                  backgroundImage: AssetImage('images/IMG-20190405-WA0005.jpg'),
                ),
                SizedBox(width: 10.w,),
                Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                        'Mr Lackshya Mathur',
                      style: TextStyle(
                        fontWeight: FontWeight.w800,
                        fontSize: 16.sp,
                        color: Color(0xFF393939),
                      ),
                    ),
                    SizedBox(height: 5.h,),
                    StreamBuilder(
                        stream: _dbref.onValue,
                        builder: (context, AsyncSnapshot snap) {
                          if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                            return Text(
                              'Last Updated: $lastUpdateHour:$lastUpdateMin $lastUpdateDay/$lastUpdateMonth/$lastUpdateYear',
                              style: TextStyle(
                                fontWeight: FontWeight.w700,
                                fontSize: 10.sp,
                                color: Color(0XFF008A1E),
                              ),
                            );
                          } else {
                            return Center (child: Text('--'),);
                          }
                        }
                    ),

                  ],
                ),
              ],
            ),
          ),
        ),
        actions: [
          GestureDetector(
            onTap: () async {
              var url = Uri.https('drive.google.com', '/file/d/1Lhp2K_gCbKxx8E3TwHet2EeOAMpiGEvJ/view?usp=sharing');
              if (await canLaunchUrl(url)) {
                await launchUrl(url);
              }
            },
            child: Container(
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(20),
                color: Color(0xFF008A1E),
              ),
              width: 86.w,
              height: 50.h,
              child: Center(
                child: Text(
                  'View Chart',
                  style: TextStyle(
                    fontWeight: FontWeight.w800,
                    fontSize: 12.sp,
                    color: Color(0xFFFFFFFF),
                  ),
                ),
              ),
            ),
          ),
          SizedBox(width: 20.w,)
        ],
      ),
      body: SingleChildScrollView(
        child: Padding(
          padding: EdgeInsets.symmetric(horizontal: 20.w),
          child: Column(
            children: [
              SizedBox(height: 10.h,),
              Row(
                children: [
                  Container(
                    decoration: BoxDecoration(
                      color: Color(0xFFF6F6F6),
                      borderRadius: BorderRadius.circular(20)
                    ),
                    width: 102.w,
                    height: 44.h,
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Icon(
                            Icons.person,
                        ),
                        StreamBuilder(
                            stream: _dbref.onValue,
                            builder: (context, AsyncSnapshot snap) {
                              if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                var motionStateDisplay = 'Resting';
                                if (motionState == 1) {
                                  motionStateDisplay = 'Moving';
                                } else {
                                  motionStateDisplay = 'Resting';
                                }
                                return Text(
                                  '$motionStateDisplay',
                                  style: TextStyle(
                                    fontWeight: FontWeight.w800,
                                    fontSize: 12.sp,
                                  ),
                                );
                              } else {
                                return Center (child: Text('--'),);
                              }
                            }
                        ),

                      ],
                    ),
                  ),
                  SizedBox(width: 10.w,),
                  Container(
                    decoration: BoxDecoration(
                        color: Color(0xFFF6F6F6),
                        borderRadius: BorderRadius.circular(20)
                    ),
                    width: 208.w,
                    height: 44.h,
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Text(
                          'Room',
                          style: TextStyle(
                            fontWeight: FontWeight.w800,
                            fontSize: 16.sp,
                          ),
                        ),
                        Container(
                          child: Row(
                            children: [
                              Icon(Icons.thermostat),
                              StreamBuilder(
                                stream: _dbref.onValue,
                                builder: (context, AsyncSnapshot snap) {
                                  if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                    var roomTempInt = roomTemperature.toInt();
                                    return Text(
                                      '$roomTempInt°C',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                      ),
                                    );
                                  } else {
                                    return Center (child: Text('--'),);
                                  }
                                }
                              ),
                            ],
                          ),
                        ),
                        Container(
                          child: Row(
                            children: [
                              Icon(Icons.water_drop),
                              StreamBuilder(
                                  stream: _dbref.onValue,
                                  builder: (context, AsyncSnapshot snap) {
                                    if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                      return Text(
                                        '$roomHumidity%',
                                        style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 16.sp,
                                        ),
                                      );
                                    } else {
                                      return Center (child: Text('--'),);
                                    }
                                  }
                              ),

                            ],
                          ),
                        )
                      ],
                    ),
                  ),
                ],
              ),
              SizedBox(height: 20.h,),
              Stack(
                children: [
                  Container(
                    decoration: BoxDecoration(
                        color: Color(0xFFF6F6F6),
                        borderRadius: BorderRadius.circular(20)
                    ),
                    width: 1000.w,
                    height: 160.h,
                    child: Align(
                      alignment: Alignment.centerLeft,
                      child: Padding(
                        padding: EdgeInsets.all(10.0.w),
                        child: Container(
                          width: 210.w,
                          child: SfSparkLineChart(
                            width: 3,
                            trackball: SparkChartTrackball(
                            ),
                            isInversed: false,
                            axisLineWidth: 0,
                            marker: SparkChartMarker(
                              displayMode: SparkChartMarkerDisplayMode.all,
                            ),
                            data: heartRateList.toList(),
                          ),
                        ),
                      ),
                    ),
                  ),
                  Align(
                    alignment: Alignment.centerRight,
                    child: Container(
                      decoration: BoxDecoration(
                          color: Color(0xFF0F4485),
                          borderRadius: BorderRadius.circular(20)
                      ),
                      width: 90.w,
                      height: 160.h,
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          StreamBuilder(
                              stream: _dbref.onValue,
                              builder: (context, AsyncSnapshot snap) {
                                if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                  // if (!heartRateList.contains(heartRate)) {
                                  //   heartRateList.add(heartRate);
                                  //   print(heartRateList);
                                  // }
                                  var heartRateInt = heartRate.toInt();
                                  return Text(
                                    '$heartRateInt',
                                    style: TextStyle(
                                      fontWeight: FontWeight.w800,
                                      fontSize: 28.sp,
                                      color: Colors.white,
                                    ),
                                  );
                                } else {
                                  return Center (child: Text('--'),);
                                }
                              }
                          ),
                          Column(
                            children: [
                              Text(
                                'HR',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 18.sp,
                                  color: Colors.white,
                                ),
                              ),
                              Text(
                                'bpm',
                                style: TextStyle(
                                  fontWeight: FontWeight.w400,
                                  fontSize: 12.sp,
                                  color: Colors.white,
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              ),
              SizedBox(height: 10.h,),
              Stack(
                children: [
                  Container(
                    decoration: BoxDecoration(
                        color: Color(0xFFF6F6F6),
                        borderRadius: BorderRadius.circular(20)
                    ),
                    width: 1000.w,
                    height: 160.h,
                    child: Align(
                      alignment: Alignment.centerLeft,
                      child: Padding(
                        padding: EdgeInsets.all(10.0.w),
                        child: Container(
                          width: 210.w,
                          child: SfSparkLineChart(
                            width: 3,
                            trackball: SparkChartTrackball(
                            ),
                            isInversed: false,
                            axisLineWidth: 0,
                            marker: SparkChartMarker(
                              displayMode: SparkChartMarkerDisplayMode.all,
                            ),
                            data: bloodOxygenList.toList(),
                          ),
                        ),
                      ),
                    ),
                  ),
                  Align(
                    alignment: Alignment.centerRight,
                    child: Container(
                      decoration: BoxDecoration(
                          color: Color(0xFF0F4485),
                          borderRadius: BorderRadius.circular(20)
                      ),
                      child: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        StreamBuilder(
                            stream: _dbref.onValue,
                            builder: (context, AsyncSnapshot snap) {
                              if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                return Text(
                                  '$bloodOxygen',
                                  style: TextStyle(
                                    fontWeight: FontWeight.w800,
                                    fontSize: 28.sp,
                                    color: Colors.white,
                                  ),
                                );
                              } else {
                                return Center (child: Text('--'),);
                              }
                            }
                        ),
                        Column(
                          children: [
                            Text(
                              'SpO2',
                              style: TextStyle(
                                fontWeight: FontWeight.w800,
                                fontSize: 18.sp,
                                color: Colors.white,
                              ),
                            ),
                            Text(
                              '%',
                              style: TextStyle(
                                fontWeight: FontWeight.w400,
                                fontSize: 12.sp,
                                color: Colors.white,
                              ),
                            ),
                          ],
                        ),
                      ],
                    ),
                      width: 90.w,
                      height: 160.h,
                    ),
                  ),
                ],
              ),
              SizedBox(height: 10.h,),
              Stack(
                children: [
                  Container(
                    decoration: BoxDecoration(
                        color: Color(0xFFF6F6F6),
                        borderRadius: BorderRadius.circular(20)
                    ),
                    width: 1000.w,
                    height: 160.h,
                    child: Align(
                      alignment: Alignment.centerLeft,
                      child: Padding(
                        padding: EdgeInsets.all(10.0.w),
                        child: Container(
                          width: 210.w,
                          child: SfSparkLineChart(
                            axisLineColor: Colors.red,
                            axisCrossesAt: 100.4,
                            width: 3,
                            trackball: SparkChartTrackball(
                            ),
                            isInversed: false,
                            axisLineWidth: 1,
                            marker: SparkChartMarker(
                              displayMode: SparkChartMarkerDisplayMode.all,
                            ),
                            data: bodyTemperatureList.toList(),
                          ),
                        ),
                      ),
                    ),
                  ),
                  Align(
                    alignment: Alignment.centerRight,
                    child: Container(
                      decoration: BoxDecoration(
                          color: Color(0xFF0F4485),
                          borderRadius: BorderRadius.circular(20)
                      ),
                      width: 90.w,
                      height: 160.h,
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          StreamBuilder(
                              stream: _dbref.onValue,
                              builder: (context, AsyncSnapshot snap) {
                                if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                  String formattedBTemp = bodyTemperature.toStringAsFixed(1);
                                  return Column(
                                    children: [
                                       bodyTemperature < 100.4
                                           ? SizedBox(width: 0, height: 0,)
                                           :Container(
                                        decoration: BoxDecoration(
                                          color: Color(0xFFFF4343),
                                          borderRadius: BorderRadius.circular(20),
                                        ),
                                        width: 70.w,
                                        height: 20.h,
                                        child: Center(
                                          child: Text(
                                            'FEVER',
                                            style: TextStyle(
                                              fontWeight: FontWeight.w800,
                                              fontSize: 10.sp,
                                              color: Colors.white,
                                            ),
                                          ),
                                        ),
                                      ),
                                      Text(
                                        '$formattedBTemp',
                                        style: TextStyle(
                                          fontWeight: FontWeight.w800,
                                          fontSize: 28.sp,
                                          color: Colors.white,
                                        ),
                                      ),
                                    ],
                                  );
                                } else {
                                  return Center (child: Text('--'),);
                                }
                              }
                          ),
                          Column(
                            children: [
                              Text(
                                'B Temp',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 18.sp,
                                  color: Colors.white,
                                ),
                              ),
                              Text(
                                '°F',
                                style: TextStyle(
                                  fontWeight: FontWeight.w400,
                                  fontSize: 12.sp,
                                  color: Colors.white,
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              ),
              SizedBox(height: 10.h,),
              Stack(
                children: [
                  Container(
                    decoration: BoxDecoration(
                        color: Color(0xFFF6F6F6),
                        borderRadius: BorderRadius.circular(20)
                    ),
                    width: 220.w,
                    height: 160.h,
                    child: Padding(
                      padding: EdgeInsets.all(10.0.w),
                      child: StreamBuilder(
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                              return SfLinearGauge(
                                interval: 120,
                                axisTrackStyle: LinearAxisTrackStyle(
                                    thickness: 12,
                                  color: Colors.white,
                                ),
                                barPointers: [
                                LinearBarPointer(
                                  value: totalSleep.toDouble(),
                                  thickness: 12,
                                ),
                                ],
                                minimum: 0,
                                maximum: 720,
                                ranges: [
                                  LinearGaugeRange(
                                    startValue: 0,
                                    endValue: 480,
                                    startWidth: 40,
                                    endWidth: 40,
                                    color: Colors.deepOrangeAccent,
                                    child: Center(
                                      child: Text(
                                          'INSUFFICIENT',
                                        style: TextStyle(
                                          fontWeight: FontWeight.w800,
                                          fontSize: 10.sp,
                                          color: Colors.white,
                                        ),
                                      ),
                                    ),
                                  ),
                                  LinearGaugeRange(
                                    startValue: 480,
                                    endValue: 720,
                                    startWidth: 40,
                                    endWidth: 40,
                                    color: Colors.green,
                                    child: Center(
                                      child: Text(
                                        'SUFFICIENT',
                                        style: TextStyle(
                                          fontWeight: FontWeight.w800,
                                          fontSize: 10.sp,
                                          color: Colors.white,
                                        ),
                                      ),
                                    ),
                                  )
                                ],
                              );
                            } else {
                              return Center (child: Text('--'),);
                            }
                          }
                      ),
                    )
                  ),
                  Align(
                    alignment: Alignment.centerRight,
                    child: Container(
                      decoration: BoxDecoration(
                          color: Color(0xFF0F4485),
                          borderRadius: BorderRadius.circular(20)
                      ),
                      width: 90.w,
                      height: 160.h,
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          StreamBuilder(
                              stream: _dbref.onValue,
                              builder: (context, AsyncSnapshot snap) {
                                if (snap.hasData && !snap.hasError && snap.data.snapshot.value != null) {
                                  return Text(
                                    '$totalSleep',
                                    style: TextStyle(
                                      fontWeight: FontWeight.w800,
                                      fontSize: 28.sp,
                                      color: Colors.white,
                                    ),
                                  );
                                } else {
                                  return Center (child: Text('--'),);
                                }
                              }
                          ),
                          Column(
                            children: [
                              Text(
                                'Sleep',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 18.sp,
                                  color: Colors.white,
                                ),
                              ),
                              Text(
                                'min',
                                style: TextStyle(
                                  fontWeight: FontWeight.w400,
                                  fontSize: 12.sp,
                                  color: Colors.white,
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              ),
              SizedBox(
                height: 20.h,
              ),
              GestureDetector(
                onTap: () async {
                  // var url = Uri.https('drive.google.com', '/drive/folders/1mwjXVYltxb1LwtQdcocZOKMtL7NHm3qE?usp=sharing');
                  // if (await canLaunchUrl(url)) {
                  // await launchUrl(url);
                  // }
                  // Fluttertoast.showToast(msg: 'View Patient Documents was pressed');
                  Navigator.of(context).push(MaterialPageRoute( builder: (context) => DocumentsPage()));
                },
                child: Container(
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(20),
                    color: Color(0xFF008A1E),
                  ),
                  width: 1000.w,
                  height: 60.h,
                  child: Padding(
                    padding: EdgeInsets.symmetric(horizontal: 20.w),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Row(
                          children: [
                            Icon(
                              Icons.file_open,
                              color: Colors.white,
                            ),
                            SizedBox(
                              width: 20.w,
                            ),
                            Text(
                              'View Patient Documents',
                              style: TextStyle(
                                fontWeight: FontWeight.w800,
                                fontSize: 16.sp,
                                color: Colors.white,
                              ),
                            ),
                          ],
                        ),
                        Icon(
                          Icons.arrow_forward,
                          color: Colors.white,
                        ),
                      ],
                    ),
                  ),
                ),
              ),
              SizedBox(
                height: 20.h,
              ),
            ],
          ),
        ),
      ),
    );
  }
}

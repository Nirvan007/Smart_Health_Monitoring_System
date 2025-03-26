import 'package:flutter/material.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'data_display_widget.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'firebase service.dart';

class NewDashboard extends StatefulWidget {
  const NewDashboard({Key? key}) : super(key: key);

  @override
  State<NewDashboard> createState() => _NewDashboardState();
}

class _NewDashboardState extends State<NewDashboard> {
  late DatabaseReference _dbref;

  @override
  void initState() {
    super.initState();
    _dbref = FirebaseDatabase.instance.ref();
    readData();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xFF072448),
      body: SafeArea(
        child: Column(
          children: [
            SizedBox(
              height: 310.h,
              child: Column(
                children: [
                  SizedBox(
                    height: 24.h,
                  ),
                  Text(
                    'SEMACS',
                    style: TextStyle(
                      fontWeight: FontWeight.w600,
                      fontSize: 16.sp,
                      color: Colors.white,
                    ),
                  ),
                  SizedBox(
                    height: 30.h,
                  ),
                  const CircleAvatar(
                    maxRadius: 50,
                    backgroundColor: Colors.white,
                    backgroundImage: NetworkImage(
                      'https://thumbs.dreamstime.com/b/portrait-old-white-hair-sad-man-wear-dark-sweater-isolated-grey-background-portrait-old-white-hair-sad-man-wear-dark-208553406.jpg',
                    ),
                  ),
                  SizedBox(
                    height: 30.h,
                  ),
                  Text(
                    'Nirvan Tamhane',
                    style: TextStyle(
                      fontWeight: FontWeight.w600,
                      fontSize: 24.sp,
                      color: Colors.white,
                    ),
                  ),
                  SizedBox(
                    height: 16.h,
                  ),
                  StreamBuilder(
                    // bodytemp
                    stream: _dbref.onValue,
                    builder: (context, AsyncSnapshot snap) {
                      if (snap.hasData &&
                          !snap.hasError &&
                          snap.data.snapshot.value != null) {
                        return Text(
                          'Last Synced: $timeHr:$timeMin on $timeDay/$timeMonth/$timeYear',
                          style: TextStyle(
                            fontWeight: FontWeight.w400,
                            fontSize: 16.sp,
                            color: Colors.white,
                          ),
                        );
                      } else {
                        return const Center(child: Text("No data"));
                      }
                    },
                  ),
                ],
              ),
            ),
            Expanded(
              child: Container(
                decoration: const BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.only(
                    topLeft: Radius.circular(15),
                    topRight: Radius.circular(15),
                  ),
                ),
                child: ListView(
                  padding: EdgeInsets.only(left: 28.w, right: 28.w, top: 35.h),
                  children: [
                    Text(
                      'Body Parameters',
                      style: TextStyle(
                        fontWeight: FontWeight.w600,
                        fontSize: 24.sp,
                      ),
                    ),
                    SizedBox(
                      height: 30.h,
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        StreamBuilder(
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData &&
                                !snap.hasError &&
                                snap.data.snapshot.value != null) {
                              return Container(
                                width: 140.w,
                                height: 140.w,
                                color: Color(0xFFF8F8F8),
                                child: Column(
                                  children: [
                                    SizedBox(
                                      height: 14.h,
                                    ),
                                    Container(
                                      //color: Colors.red,
                                      width: 40.w,
                                      height: 40.w,
                                      child: Image(
                                        image: AssetImage(
                                            'icons/icons8-heart-96.png'),
                                      ),
                                    ),
                                    SizedBox(
                                      height: 18.h,
                                    ),
                                    Text(
                                      '$heartRate',
                                      style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 28.sp,
                                          color: Colors.black,
                                          overflow: TextOverflow.ellipsis),
                                    ),
                                    SizedBox(
                                      height: 16.h,
                                    ),
                                    Text(
                                      'Heart Rate (BPM)',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                        color: Colors.black,
                                      ),
                                    ),
                                  ],
                                ),
                              );
                            } else {
                              return const Center(child: Text("No data"));
                            }
                          },
                        ),
                        SizedBox(
                          width: 14.w,
                        ),
                        StreamBuilder(
                          // bodytemp
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData &&
                                !snap.hasError &&
                                snap.data.snapshot.value != null) {
                              return Container(
                                width: 140.w,
                                height: 140.w,
                                color: Color(0xFFF8F8F8),
                                child: Column(
                                  children: [
                                    SizedBox(
                                      height: 14.h,
                                    ),
                                    Container(
                                      //color: Colors.red,
                                      width: 40.w,
                                      height: 40.w,
                                      child: Image(
                                        image: AssetImage(
                                            'icons/BodyTempIcon.png'),
                                      ),
                                    ),
                                    SizedBox(
                                      height: 18.h,
                                    ),
                                    Text(
                                      '$bodyTemperature',
                                      style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 28.sp,
                                          color: Colors.black,
                                          overflow: TextOverflow.ellipsis),
                                    ),
                                    SizedBox(
                                      height: 16.h,
                                    ),
                                    Text(
                                      'Body Temp (℃)',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                        color: Colors.black,
                                      ),
                                    ),
                                  ],
                                ),
                              );
                            } else {
                              return const Center(child: Text("No data"));
                            }
                          },
                        ),
                      ],
                    ),
                    SizedBox(
                      height: 36.h,
                    ),
                    Text(
                      'Room Parameters',
                      style: TextStyle(
                        fontWeight: FontWeight.w600,
                        fontSize: 24.sp,
                      ),
                    ),
                    SizedBox(
                      height: 30.h,
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        StreamBuilder(
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData &&
                                !snap.hasError &&
                                snap.data.snapshot.value != null) {
                              return Container(
                                width: 140.w,
                                height: 140.w,
                                color: Color(0xFFF8F8F8),
                                child: Column(
                                  children: [
                                    SizedBox(
                                      height: 14.h,
                                    ),
                                    Container(
                                      //color: Colors.red,
                                      width: 40.w,
                                      height: 40.w,
                                      child: Image(
                                        image: AssetImage(
                                            'icons/Temperature Inside.png'),
                                      ),
                                    ),
                                    SizedBox(
                                      height: 18.h,
                                    ),
                                    Text(
                                      '$roomTemperature',
                                      style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 28.sp,
                                          color: Colors.black,
                                          overflow: TextOverflow.ellipsis),
                                    ),
                                    SizedBox(
                                      height: 16.h,
                                    ),
                                    Text(
                                      'Room Temp (℃)',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                        color: Colors.black,
                                      ),
                                    ),
                                  ],
                                ),
                              );
                            } else {
                              return const Center(child: Text("No data"));
                            }
                          },
                        ),
                        SizedBox(
                          width: 14.w,
                        ),
                        StreamBuilder(
                          // bodytemp
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData &&
                                !snap.hasError &&
                                snap.data.snapshot.value != null) {
                              return Container(
                                width: 140.w,
                                height: 140.w,
                                color: Color(0xFFF8F8F8),
                                child: Column(
                                  children: [
                                    SizedBox(
                                      height: 14.h,
                                    ),
                                    Container(
                                      //color: Colors.red,
                                      width: 40.w,
                                      height: 40.w,
                                      child: Image(
                                        image: AssetImage('icons/Wet.png'),
                                      ),
                                    ),
                                    SizedBox(
                                      height: 18.h,
                                    ),
                                    Text(
                                      '$roomHumidity',
                                      style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 28.sp,
                                          color: Colors.black,
                                          overflow: TextOverflow.ellipsis),
                                    ),
                                    SizedBox(
                                      height: 16.h,
                                    ),
                                    Text(
                                      'Room Humidity (%)',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                        color: Colors.black,
                                      ),
                                    ),
                                  ],
                                ),
                              );
                            } else {
                              return const Center(child: Text("No data"));
                            }
                          },
                        ),
                      ],
                    ),
                    SizedBox(
                      height: 36.h,
                    ),
                    Text(
                      'Sleep',
                      style: TextStyle(
                        fontWeight: FontWeight.w600,
                        fontSize: 24.sp,
                      ),
                    ),
                    SizedBox(
                      height: 30.h,
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        StreamBuilder(
                          stream: _dbref.onValue,
                          builder: (context, AsyncSnapshot snap) {
                            if (snap.hasData &&
                                !snap.hasError &&
                                snap.data.snapshot.value != null) {
                              return Container(
                                width: 140.w,
                                height: 140.w,
                                color: Color(0xFFF8F8F8),
                                child: Column(
                                  children: [
                                    SizedBox(
                                      height: 14.h,
                                    ),
                                    Container(
                                      //color: Colors.red,
                                      width: 40.w,
                                      height: 40.w,
                                      child: Image(
                                        image: AssetImage(
                                            'icons/Sleeping in Bed.png'),
                                      ),
                                    ),
                                    SizedBox(
                                      height: 18.h,
                                    ),
                                    Text(
                                      '$totalSleep',
                                      style: TextStyle(
                                          fontWeight: FontWeight.w600,
                                          fontSize: 28.sp,
                                          color: Colors.black,
                                          overflow: TextOverflow.ellipsis),
                                    ),
                                    SizedBox(
                                      height: 16.h,
                                    ),
                                    Text(
                                      'Total Sleep (Min)',
                                      style: TextStyle(
                                        fontWeight: FontWeight.w600,
                                        fontSize: 16.sp,
                                        color: Colors.black,
                                      ),
                                    ),
                                  ],
                                ),
                              );
                            } else {
                              return const Center(child: Text("No data"));
                            }
                          },
                        ),
                        SizedBox(
                          width: 14.w,
                        ),
                      ],
                    ),
                    SizedBox(
                      height: 50.h,
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

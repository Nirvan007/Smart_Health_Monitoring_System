import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:line_icons/line_icons.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'firebase service.dart';

class Dashboard extends StatefulWidget {
  const Dashboard({Key? key}) : super(key: key);

  @override
  State<Dashboard> createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  late DatabaseReference _dbref;

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    _dbref = FirebaseDatabase.instance.ref();
    readData();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        toolbarHeight: 100,
        elevation: 0.0,
        title: Column(
          children: const [
            Text(
              'SEMACS',
              style: TextStyle(
                fontSize: 28.0,
                fontWeight: FontWeight.bold,
              ),
            ),
            SizedBox(
              height: 10,
            ),
            Text(
              'CONNECTED',
              style: TextStyle(
                fontSize: 14,
                //fontWeight: FontWeight.normal,
                color: Colors.lightGreenAccent,
              ),
            ),
          ],
        ),
        backgroundColor: Colors.indigo,
        centerTitle: true,
      ),
      backgroundColor: Colors.white,
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 20.0),
          child: GridView(
            gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
              crossAxisCount: 2,
              crossAxisSpacing: 20,
              mainAxisSpacing: 20,
            ),
            children: [
              StreamBuilder(
                stream: _dbref.onValue,
                builder: (context, AsyncSnapshot snap) {
                  if (snap.hasData &&
                      !snap.hasError &&
                      snap.data.snapshot.value != null) {
                    //Map data = snap.data.snapshot.value;
                    //List item = [];
                    // data.forEach(
                    //     (index, data) => item.add({"key": index, ...data}));
                    return Container(
                      color: Colors.grey.shade100,
                      child: Column(
                        children: [
                          const SizedBox(
                            height: 20,
                          ),
                          const Icon(
                            LineIcons.highTemperature,
                            size: 36,
                          ),
                          const SizedBox(
                            height: 15,
                          ),
                          Text(
                            '$bodyTemperature',
                            style: const TextStyle(
                              fontSize: 36,
                            ),
                          ),
                          const SizedBox(
                            height: 15,
                          ),
                          const Text(
                            'Body Temp',
                            style: TextStyle(
                              fontSize: 20,
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
              Container(
                color: Colors.grey.shade100,
                child: Column(
                  children: const [
                    SizedBox(
                      height: 20,
                    ),
                    Icon(
                      Icons.circle,
                      size: 36,
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      '85',
                      style: TextStyle(
                        fontSize: 36,
                      ),
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      'SpO2',
                      style: TextStyle(
                        fontSize: 20,
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                color: Colors.grey.shade100,
                child: Column(
                  children: [
                    const SizedBox(
                      height: 20,
                    ),
                    const Icon(
                      LineIcons.thermometerEmpty,
                      size: 36,
                    ),
                    const SizedBox(
                      height: 15,
                    ),
                    const Text(
                      '',
                      style: TextStyle(
                        fontSize: 36,
                      ),
                    ),
                    const SizedBox(
                      height: 15,
                    ),
                    const Text(
                      'Body Temp',
                      style: TextStyle(
                        fontSize: 20,
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                color: Colors.grey.shade100,
                child: Column(
                  children: const [
                    SizedBox(
                      height: 20,
                    ),
                    Icon(
                      LineIcons.thermometerEmpty,
                      size: 36,
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      '85',
                      style: TextStyle(
                        fontSize: 36,
                      ),
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      'Room Temp',
                      style: TextStyle(
                        fontSize: 20,
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                color: Colors.grey.shade100,
                child: Column(
                  children: const [
                    SizedBox(
                      height: 20,
                    ),
                    Icon(
                      LineIcons.circle,
                      size: 36,
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      '85',
                      style: TextStyle(
                        fontSize: 36,
                      ),
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      'Heart Rate',
                      style: TextStyle(
                        fontSize: 20,
                      ),
                    ),
                  ],
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

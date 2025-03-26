import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:semacs_app/NewDashboard.dart';
import 'dashboard screen.dart';
import 'fypScreens/fyp_dashboard.dart';
// import 'package:line_icons/line_icons.dart';
// import 'package:firebase_database/firebase_database.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  FirebaseApp firebaseApp = await Firebase.initializeApp();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return ScreenUtilInit(
      designSize: const Size(360, 900),
      minTextAdapt: true,
      //splitScreenMode: true,
      builder: (context, child) {
        return MaterialApp(
          debugShowCheckedModeBanner: false,
          title: 'Smart Elderly Monitoring and Care System',
          theme: ThemeData(fontFamily: 'Urbanist'),
          home: FYPDashboard(),
        );
      },
    );
  }
}

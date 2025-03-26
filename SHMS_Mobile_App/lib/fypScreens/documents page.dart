import 'package:flutter/material.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:url_launcher/url_launcher.dart';

class DocumentsPage extends StatefulWidget {
  const DocumentsPage({super.key});

  @override
  State<DocumentsPage> createState() => _DocumentsPageState();
}

class _DocumentsPageState extends State<DocumentsPage> {
  @override
  Widget build(BuildContext context) {
    return SafeArea(
        child: Scaffold(
          body: Padding(
            padding: EdgeInsets.all(15.w),
            child: Column(
              children: [
                Align(
                  alignment: Alignment.centerLeft,
                  child: Text(
                    'Patient Documents',
                    style: TextStyle(
                      fontWeight: FontWeight.w800,
                      fontSize: 20.sp,
                      color: Colors.black,
                    ),
                  ),
                ),
                SizedBox(height: 18.h,),
                GestureDetector(
                  onTap: () async {
                    var url = Uri.https('drive.google.com', '/file/d/1NgagUdjl6VcKJ0RWI74W_9K3AeFf7qwZ/view?usp=sharing');
                    if (await canLaunchUrl(url)) {
                    await launchUrl(url);
                    }
                    // Fluttertoast.showToast(msg: 'View Patient Documents was pressed');
                  },
                  child: Container(
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(20),
                      color: Color(0xFFF6F6F6),
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
                                color: Colors.black,
                              ),
                              SizedBox(
                                width: 20.w,
                              ),
                              Text(
                                'MRI REPORT',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 16.sp,
                                  color: Colors.black,
                                ),
                              ),
                            ],
                          ),
                          Icon(
                            Icons.arrow_forward,
                            color: Colors.black,
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
                SizedBox(height: 15.h,),
                GestureDetector(
                  onTap: () async {
                    var url = Uri.https('drive.google.com', '/file/d/1pACnFInUoeT8DCGRWx_D0CV8DwBtCwjc/view?usp=sharing');
                    if (await canLaunchUrl(url)) {
                    await launchUrl(url);
                    }
                    // Fluttertoast.showToast(msg: 'View Patient Documents was pressed');
                  },
                  child: Container(
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(20),
                      color: Color(0xFFF6F6F6),
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
                                color: Colors.black,
                              ),
                              SizedBox(
                                width: 20.w,
                              ),
                              Text(
                                'X-RAY REPORT',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 16.sp,
                                  color: Colors.black,
                                ),
                              ),
                            ],
                          ),
                          Icon(
                            Icons.arrow_forward,
                            color: Colors.black,
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
                SizedBox(height: 15.h,),
                GestureDetector(
                  onTap: () async {
                    var url = Uri.https('drive.google.com', '/file/d/13io8dCx_FkuRKxIirY2Hyys71zjsyM36/view?usp=sharing');
                    if (await canLaunchUrl(url)) {
                    await launchUrl(url);
                    }
                    // Fluttertoast.showToast(msg: 'View Patient Documents was pressed');
                  },
                  child: Container(
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(20),
                      color: Color(0xFFF6F6F6),
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
                                color: Colors.black,
                              ),
                              SizedBox(
                                width: 20.w,
                              ),
                              Text(
                                'BLOOD TEST REPORT',
                                style: TextStyle(
                                  fontWeight: FontWeight.w800,
                                  fontSize: 16.sp,
                                  color: Colors.black,
                                ),
                              ),
                            ],
                          ),
                          Icon(
                            Icons.arrow_forward,
                            color: Colors.black,
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        )
    );
  }
}

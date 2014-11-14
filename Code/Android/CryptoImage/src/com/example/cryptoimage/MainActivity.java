package com.example.cryptoimage;

import java.io.File;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    System.loadLibrary("crypto_image");
                    Log.i("Crypto", "OpenCV loaded successfully");
                    encryptoText();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String extStorageDirectory = Environment.getExternalStorageDirectory().toString();
		
//		File file = new File(extStorageDirectory+"/Test/Files/teste.txt");
		File file = new File("/sdcard/aerial.pgm");
		
		Mat matTest = Highgui.imread("/sdcard/aerial.pgm");
		
		String[] files = file.list();
		if(files!=null)
	    for (String fileString : files) {
	       Log.d("teste",fileString);
	    }
		
		if(file.exists())
			Log.i("teste", "arquivo existe");
		else 
			Log.e("teste", "arquivo nao existe");
		
		Log.d("teste",file.getAbsolutePath());
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	
	@Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
    }
	
	
	public native String encryptoText();
	public native int parseImage(Mat image);

}

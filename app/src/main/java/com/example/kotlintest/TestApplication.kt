package com.example.kotlintest

import android.app.Application

class TestApplication : Application()
{
  override fun onCreate() {
    super.onCreate()
    System.loadLibrary("Player")
  }
}
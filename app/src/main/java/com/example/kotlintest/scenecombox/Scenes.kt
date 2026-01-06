package com.example.kotlintest.scenecombox

enum class Scenes(val id: Int) {
  Unknown(0),
  Sponza(1),
  Helmet(2);

  companion object {
    fun fromId(id: Int): Scenes{
      return entries.find { it.id == id } ?: Unknown
    }
  }
}
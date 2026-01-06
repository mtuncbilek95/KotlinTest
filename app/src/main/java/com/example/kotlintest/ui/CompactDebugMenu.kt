package com.example.kotlintest.ui

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.runtime.*
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.kotlintest.scenecombox.Scenes

import androidx.compose.material.icons.filled.ArrowDropDown
import com.example.kotlintest.callbacks.LoadCallbacks

@Composable
fun CompactDebugMenu() {
  var isDropdownExpanded by remember { mutableStateOf(false) }
  var selectedScene by remember { mutableStateOf(Scenes.entries.firstOrNull() ?: Scenes.Unknown) }

  Column(
    modifier = Modifier.padding(10.dp),
    horizontalAlignment = Alignment.CenterHorizontally
  ) {
    Text(
      text = "DEBUG MENU",
      color = Color.LightGray,
      fontSize = 10.sp,
      fontWeight = FontWeight.Bold,
      modifier = Modifier.fillMaxWidth()
    )

    Spacer(modifier = Modifier.height(8.dp))

    Box(
      modifier = Modifier
        .fillMaxWidth()
        .height(28.dp)
        .background(Color(0xFF2D2D2D), RoundedCornerShape(4.dp))
        .border(1.dp, Color(0xFF555555), RoundedCornerShape(4.dp))
        .clickable { isDropdownExpanded = true }
    ) {

      Row(
        modifier = Modifier
          .fillMaxSize()
          .padding(horizontal = 8.dp),
        verticalAlignment = Alignment.CenterVertically,
        horizontalArrangement = Arrangement.SpaceBetween // İki uca yasla
      ) {
        Text(
          text = selectedScene.name,
          color = Color.White,
          fontSize = 12.sp,
          maxLines = 1
        )

        Icon(
          imageVector = androidx.compose.material.icons.Icons.Default.ArrowDropDown,
          contentDescription = "Select",
          tint = Color.LightGray,
          modifier = Modifier.size(16.dp) // Küçük, kibar ikon
        )
      }

      DropdownMenu(
        expanded = isDropdownExpanded,
        onDismissRequest = { isDropdownExpanded = false },
        modifier = Modifier
          .background(Color(0xFF2D2D2D))
          .border(1.dp, Color(0xFF555555))
      ) {
        Scenes.entries.forEach { scene ->
          DropdownMenuItem(
            text = {
              Text(
                scene.name,
                color = if (selectedScene == scene) Color(0xFF4CAF50) else Color.White,
                fontSize = 12.sp
              )
            },
            onClick = {
              selectedScene = scene
              isDropdownExpanded = false
            },
            contentPadding = PaddingValues(horizontal = 8.dp, vertical = 0.dp),
            modifier = Modifier.height(28.dp)
          )
        }
      }
    }

    Spacer(modifier = Modifier.height(8.dp))

    Button(
      onClick = { LoadCallbacks.LoadScene(selectedScene) },
      colors = ButtonDefaults.buttonColors(containerColor = Color(0xFF009688)),
      contentPadding = PaddingValues(0.dp),
      modifier = Modifier.fillMaxWidth().height(32.dp),
      shape = RoundedCornerShape(4.dp)
    ) {
      Text("LOAD", color = Color.White, fontSize = 12.sp, fontWeight = FontWeight.Bold)
    }
  }
}
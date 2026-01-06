package com.example.kotlintest.ui

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp

@Composable
fun GameOverlay() {
  Box(
    modifier = Modifier
      .fillMaxSize()
      .padding(16.dp)
  ) {
    Card(
      modifier = Modifier
        .align(Alignment.TopEnd)
        .width(180.dp),
      shape = RoundedCornerShape(8.dp),
      colors = CardDefaults.cardColors(
        containerColor = Color.Black.copy(alpha = 0.6f)
      )
    ) {
      CompactDebugMenu()
    }
  }
}

@Preview(
  name = "Game Overlay Preview",
  widthDp = 780,
  heightDp = 360,
  showBackground = true,
  backgroundColor = 0xFF009900
)
@Composable
fun PreviewGameOverlay() {
  MaterialTheme {
    GameOverlay()
  }
}
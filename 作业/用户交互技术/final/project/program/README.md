# AR Sci-Fi Planet Blind Box

## Project Introduction

AR Sci-Fi Planet Blind Box is a web-based Augmented Reality (AR) application developed using A-Frame and AR.js. Users can scan a Hiro Marker through their webcam and interact with a virtual blind box system to randomly obtain planets from the solar system.

The project combines AR technology, gamification, and educational content to create an immersive and engaging user experience.

This project was developed as the final project for the Human-Computer Interaction (HCI) course.

---

## Project Objectives

The objectives of this project are:

- Explore the application of Augmented Reality in interactive systems.
- Design an engaging blind-box interaction mechanism.
- Enhance user engagement through random reward systems.
- Present astronomy-related content in an immersive way.
- Demonstrate the integration of Web-based AR technologies.

---

## Features

### 1. Marker-Based AR Interaction

The system uses the Hiro Marker provided by AR.js.

When the camera detects the marker:

- A virtual object appears in the real-world environment.
- The object remains attached to the marker.
- Users can view the object from different angles.

### 2. Blind Box Mechanism

Users can click the **"Open Cosmic Blind Box"** button to open a virtual blind box.

A random planet will be selected according to predefined probabilities and displayed in the AR scene.

### 3. Realistic Planet Models

The application uses high-quality planetary textures for:

- Earth
- Mars
- Jupiter
- Saturn
- Uranus
- Neptune

Additional visual effects include:

- Earth atmospheric layer
- Saturn ring system
- Continuous rotation animation
- Dynamic lighting

### 4. Rarity System

The blind box includes a rarity mechanism inspired by modern collectible games.

| Rarity | Planet | Probability |
|---------|---------|-------------|
| SSR | Earth | 5% |
| SR | Saturn | 15% |
| R | Jupiter | 25% |
| N | Neptune | 20% |
| N | Uranus | 15% |
| N | Mars | 20% |

This design increases replayability and user engagement.

---

## Technologies Used

### Front-End

- HTML5
- CSS3
- JavaScript

### AR Framework

- A-Frame 1.0.4
- AR.js 3.4.8

### Rendering Engine

- Three.js
- WebGL

### Assets

- Solar System Texture Maps
- Hiro Marker

---

## Project Structure

```text
Project Folder
│
├── index.html
├── earth.jpg
├── mars.jpg
├── jupiter.jpg
├── saturn.jpg
├── saturn_ring_alpha.png
├── uranus.jpg
└── neptune.jpg
```

---

## How to Run

### Step 1

Open the project folder in Visual Studio Code.

### Step 2

Install the **Live Server** extension.

### Step 3

Right-click `index.html`.

Select:

```text
Open with Live Server
```

### Step 4

Allow camera access when prompted by the browser.

### Step 5

Show a Hiro Marker to the webcam.

### Step 6

Click **"Open Cosmic Blind Box"** to obtain a random planet.

---

## User Interaction Flow

1. Launch the application.
2. Grant camera permissions.
3. Scan the Hiro Marker.
4. The mystery box appears in AR.
5. Click the blind-box button.
6. The system randomly selects a planet.
7. The selected planet appears in the AR scene.
8. Users can continue opening blind boxes.

---

## HCI Design Considerations

### Visibility

Important information and system status are displayed at the top of the interface.

### Feedback

The system immediately informs users of the obtained reward after each interaction.

### Consistency

A unified sci-fi visual style is maintained throughout the application.

### Engagement

The rarity system encourages repeated interactions and exploration.

### Accessibility

The project runs directly in a web browser without requiring additional software installation.

---

## ⚠ Challenges and Solutions

### Problem 1: Texture Loading Failure

Planet textures could not be displayed when the project was opened using the `file://` protocol.

**Solution**

Run the project through a local server such as Live Server.

### Problem 2: Incorrect Planet Textures

General internet images caused distortion when applied to sphere models.

**Solution**

Use dedicated equirectangular planetary texture maps designed for 3D rendering.

---

## Future Improvements

- Add opening animations and particle effects.
- Add background music and sound effects.
- Expand the planet collection.
- Add a collection album system.
- Display educational information for each planet.
- Support markerless AR experiences.

---

## Conclusion

The AR Sci-Fi Planet Blind Box demonstrates how Augmented Reality can be combined with gamification to create an engaging and educational interactive experience.

By integrating marker tracking, 3D visualization, realistic planetary models, and a probability-based reward system, the project provides an effective example of Human-Computer Interaction design in a web-based AR environment.
<h1 align="center"> 📈 Derivatives (F&O) Trade Simulator & Payoff Analyzer </h1>

<p align="center">
  <i>A robust C-based terminal engine for simulating options trading. 🚀 <b>Currently evolving into a full MERN-stack SaaS platform!</b></i>
</p>

---

### 🌟 Project Engine & Workflow
<b>This project acts as a mathematical engine that takes option variables and outputs exact financial risk.</b> It is built entirely in C for rapid execution and flawless memory management.

### ✨ Deep Dive: Features & How They Work

- 📥 **Interactive Trade Input:** **How it works:** The terminal interface prompts the user to input their specific trade variables, including **Option Type (Call/Put), Position (Buy/Sell), Strike Price, Premium, and Lot Size.**

- 🧮 **Automated Risk & Reward Calculator:** **How it works:** Using core mathematical formulas, the C program instantly computes the absolute **Maximum Profit, Maximum Loss, and the exact Break-Even Point** for the entered trade, eliminating manual guesswork before entering a real market.

- 🎯 **Target Price Simulation:** **How it works:** Users can input a hypothetical "Expiry Day Price" for the underlying asset. **The program calculates the intrinsic value at that exact price point and subtracts the premium to show the absolute Net Profit or Loss (P&L).**

- 🧩 **Multi-Leg Strategy Logic:** **How it works:** The simulator allows users to stack multiple positions together. **It iterates through the inputted trades and aggregates the data to show the combined net payoff, allowing users to test complex strategies like Straddles, Strangles, or Bull/Bear Spreads.**

- ⚡ **Clean Terminal Data Display:**
  **How it works:** It utilizes standard C formatting to generate clean, readable data tables directly in the command line, keeping the application lightweight and blazing fast.

---

### 🛠️ Technology Stack
- <b>Core Engine:</b> C Programming 
- <b>Upcoming SaaS Architecture:</b> React.js, Node.js, Express, MongoDB

### 🚀 Local Execution
**To see the logic in action, simply compile the source code using any standard C compiler (like GCC):**

1. Clone the repository and navigate to the folder.
2. Compile the code: `gcc main.c -o trade_simulator`
3. Run the executable: `./trade_simulator`

<b>Follow the on-screen terminal prompts to enter your trade data and analyze the payoff results!</b>

---
<b>👨‍💻 Developed by Devarsh Patel</b>

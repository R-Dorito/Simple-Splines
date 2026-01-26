<h1>Simple curves with Raylib</h1>
<h2>What makes this different?</h2>
<p>There are many ways to create a curve, I had recently found this out when I first started this project.
Originally I had wanted to create Bezier Curves and Splines as the how to guide told me that this was a great introductory project to C and C++. I didn't know any better and took the challenge. 
Oh, how I was wrong.</p>
<p>I wanted to create my own curves, not using the ones that had already come with a library package, like the ones Raylib had come with. No, I wanted to create it myself using the original mathematics, and I managed to get there.</p>

<h2>Bezier Curves</h2>
<h3>Bernstein</h3>
<p>The Bezier curve was the first to be created and I had used Bernstein's equation, which is given as follows:</p>
<p>
$$
  B(t) = \sum_{i=0}^{n} \binom{n}{i} t^i (1 - t)^{n - i}{P}_i, 0 &le; t &le; 1 
$$
</p>
<p>
Here, <em>t</em> represents time, <em>n</em> is the number of control points that define the curve, and <em>i</em> is the value used when iterating through those control points during segment calculations. The term <strong>P<sub>i</sub></strong> refers to my Balls, which act as the control points for the Bézier curve.
Using the above equation, I can then determine the location of the curve's x and y coordinates by multiplying the results with each of the control points (Balls in my program) X and Y positions.
</p>
<p>Issues faced. Although it was fun to work with Bernstein's equation to determine the location of the curves, I had noticed that it was very limited in what it could do and I had run into a lot of issues with calculations and computer lag due to the instability of high Balls count and the amount of calculations required to render the curve. It was expensive. </p>

<h3>De Casteljau</h3>
<p>After creating the Bezier curve with Bernstein's equation, I noticed that my computer started to lag once I added in the 20th Ball to my drawing. The issue here was due to the program and the way Bernstein's equation calculates the curve. The curve is calculated using each of the control points, and as the equation is recursive, more control points meant that the equation became longer and longer. I needed a method to fix this.</p>
<p>De Casteljau's equation had offered a more recursive algortithm that would allow me to have as many control points as I wanted without overly taxing the computer. It was recursive and meant that only a single point on a curve would be rendered based on the location of the Control Points and it is calculated using linear interpolation.</p>
<p>The equation for De Casteljau is similar to Bernstein's, however, the function is </p>
<p>
  $$
  B(t) = \sum_{i=0}^{n}B_{i}b_{i,n}(t)
  $$
  where, just like Bernstein's equation above:
  $$
  b_{i,n}(t) = \binom{n}{i} t^i (1 - t)^{n - i}{P}_i
  $$
</p>
<p>The algorithm with take all values of the control point and using linear interpolation, determine a single point on the curve.</p>

<h2>Splines</h2>
<h2>Cox de Boor</h2>
<p>Splines are a different sort of curve. It is different to the normal Bezier curves as the control points of a curve does not alter the full curve drawing path. Instead, a single point can be moved around and altered wihtout affecting the full curve's position. Within the Spline calculation, I had used Cox de Boor's algorithm to determine the position of the curves.</p>
<p>  Cox de Boor's algorithm is given as follows:</p>
<p>
$$     
B_{i,0}(t) :=
\left\{
  \begin{array}{ll}
    1 & \text{if } t_i &le; x < t_{i+1} \\
    0 & \text{otherwise }
  \end{array}
\right.
$$
$$
B_{i,p}(t) = \frac{x - t_i}{t_{i+p} - t_i} \, B_{i,p-1}(x) 
           + \frac{t_{i+p+1} - x}{t_{i+p+1} - t_{i+1}} \, B_{i+1,p-1}(x)
$$
</p>
<p>Where x is the iterator over the line segment between two balls, $$t_i$$ and $$t_{i+1}$$ are the knots (which can be either 0, 1, or a number in between both of these.</p>
<p>Compared to Bezier curves, Splines are much more complex to calculate numarically as we introduce new concepts like knots and the degree of spline. Each spline curve comes with different settings, it can be clamped at both sides, like what I have done within this program, or it can begin where it naturally would start, somewhere in between the two points. </p>
<p>I wanted mine to clamp down in between the first and last control points however, the knot vectors (which is used to calculate the location of the spline) changes based on the number of knots you have in the spline. This could be solved by creating a formular to update the knots vector whenever there is a new control point in the drawing.</p>

<h2>Visuals</h2>
<p>Explaining all that is hard, heres some videos of the program running.</p>
[Watch video](path/to/video.mp4)

<h1>Simple curves with Raylib</h1>
<h2>What makes this different?</h2>
<p>There are many ways to create a curve, I had recently found this out when I first started this project.
Originally I had wanted to create Bezier Curves and Splines as the how to guide told me that this was a great introductory project to C and C++. I didn't know any better and took the challenge. 
Oh, how I was wrong.</p>
<p>I wanted to create my own curves, not using the ones that had already come with a library package, like the ones Raylib had come with. No, I wanted to create it myself using the original mathematics, and I managed to get there.</p>

<h2>Bezier Curves</h2>
<p>The Bezier curve was the first to be created and I had used Bernstein's equation, which is given as follows:</p>
<p>
$$
\mathbf{B}(t) = \sum_{i=0}^{n} \binom{n}{i} t^i (1 - t)^{n - i}\mathbf{P}_i
$$
</p>
<p>where t = time, n = number of control points within the curve, and i = the reference number used when creating for loops or segement calculation points. Finally, $$\mathbf{P}_i$$ is my Balls.
Using the above equation, I can then determine the location of the x and y coordinates by multiplying the results with the control points (Balls in my program) X and Y positions, and add it to the graph's plotting location.</p>

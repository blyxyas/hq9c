use clap::Parser;
use std::fs::{self, File};
use std::io::prelude::*;

#[derive(Parser, Debug)]
#[clap(name = "GQ9+c")]
#[clap(author = "Alex G. C. <blyxyas@gmail.com>")]
#[clap(version = "0.0")]
#[clap(about = "Compile your .hq9p files, in the great programming language of HQ9+!")]
struct Args {
    /// The inputfile, it can also be
    inputfile: String,

    #[clap(short)]
    outputfile: String,

    #[clap(short, default_value = "99")]
    bottlesno: u8,

    #[clap(short, default_value = "true")]
    verbosity: bool,
}

fn main() -> std::io::Result<()> {
    let args = Args::parse();

    // Read file to string
    let data = fs::read_to_string(args.inputfile).expect("Couldn't open the file");
    let quine: &str = &format!("println!(\"{}\");", data);

    // 256 / 4 = 64 so:
    // 1 = 64
    // 2 = 128
    // 3 = 192
    // 4 = 255
    let mut result: Vec<&str> = Vec::new();
    result.push("fn main() {\nlet mut accumulator = 0;");
    for ch in data.chars() {
        match ch {
				'H' => {
					result.push("println!(\"Hello world!\");");
				},
				'Q' => {
					result.push(quine);
				},
				'9' => {
					result.push("let mut current = 99; while current >= 1 { println!(\"{} bottles of beer\\nyou take one down, pass it around,\\n{} bottles of beer on the wall.\\n\", current, current - 1); current-= 1; }")
				},
				'+' => {
					result.push("accumulator += 1;")
				}
				_ => {},
			}
    }

    result.push("}");
    let mut file = File::create(args.outputfile)?;
    file.write_all(result.join("\n\t").as_bytes())?;
    Ok(())
}

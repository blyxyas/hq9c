use clap::Parser;
use tempfile::tempdir;

use std::fs::{self, File};
use std::io::prelude::*;
// use std::path::Path;
use std::process::Command;

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

	#[clap(short, default_value = "false")]
    debug: bool,

	#[clap(short, default_value = "false i think")]
    kitchen_mode: bool,

	#[clap(short, default_value = "false")]
    actually_built_in_java: bool,
}

fn main() -> std::io::Result<()> {
    let args = Args::parse();

    // Read file to string
    let data = fs::read_to_string(args.inputfile).expect("Couldn't open the file");
    let quine: &str = &format!("println!(\"{}\");", data);
	let currentbottle = &format!("let mut current = {};", args.bottlesno);

    // 256 / 4 = 64 so:
    // 1 = 64
    // 2 = 128
    // 3 = 192
    // 4 = 255
    let mut result: Vec<&str> = Vec::new();
    result.push("fn main() {\n\tlet mut accumulator = 0;");
    for ch in data.chars() {
        match ch {
				'H' => {
					result.push("println!(\"Hello world!\");");
				},
				'Q' => {
					result.push(quine);
				},
				'9' => {
					result.push(currentbottle);
					result.push("while current >= 1 { println!(\"{} bottles of beer\\nyou take one down, pass it around,\\n{} bottles of beer on the wall.\\n\", current, current - 1); current-= 1; }")
				},
				'+' => {
					result.push("accumulator += 1;")
				}
				_ => {},
			}
    }

    result.push("}");

	let dir = tempdir()?;
	let file_path = &dir.path().join("out.rs").as_os_str().to_str().unwrap().to_string();

    let mut file = File::create(file_path).expect("Couldn't create");
    writeln!(file, "{}", result.join("\n\t"))?;

    // Compile that new Rust tempfile.
    let _compile_out = match Command::new(format!(
			"rustc"
		)).args([file_path, "-o", &args.outputfile])
		.status() {
		Ok(_) => { Ok(()) },
		Err(e) => { println!("{}", e); Err(()) },
	};

	if std::env::consts::OS == "windows" {
		let _ = Command::new("del").args(&["/f", file_path]).status();
	} else {
		let _ = Command::new("rm").args(&["-r", file_path]);
	}

    Ok(())
}

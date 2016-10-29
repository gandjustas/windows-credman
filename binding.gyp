{
    "targets": [
        {
            "target_name": "windows-credman",
            "sources": [ "src/windows-credman.cc" ],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
        }
    ]
}